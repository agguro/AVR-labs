#!/usr/bin/env python3

import asyncio
from aiohttp import web
import socket

# Configuratie
BRIDGE_HOST = '127.0.0.1'
BRIDGE_PORT = 9999
WEB_HOST = '0.0.0.0'
WEB_PORT = 8000

WS_CLIENTS = set()

async def websocket_handler(request):
    """Beheert de WebSocket verbindingen met de browser"""
    ws = web.WebSocketResponse()
    await ws.prepare(request)
    
    WS_CLIENTS.add(ws)
    print(f"Browser verbonden. Totaal: {len(WS_CLIENTS)}")
    
    try:
        async for msg in ws:
            if msg.type == web.WSMsgType.TEXT:
                if msg.data == 'close':
                    await ws.close()
    finally:
        WS_CLIENTS.remove(ws)
        print("Browser verbroken.")
        
    return ws

async def bridge_client_task():
    """Probeert continu te verbinden met de SimAVR Bridge (Server)"""
    print(f"Bridge Client: Probeert te verbinden met {BRIDGE_HOST}:{BRIDGE_PORT}...")
    
    while True:
        reader, writer = None, None
        try:
            # Probeer verbinding te maken met de Bridge (Server)
            reader, writer = await asyncio.open_connection(BRIDGE_HOST, BRIDGE_PORT)
            print("\n[OK] Verbonden met SimAVR Bridge!")

            while True:
                # Wacht op data ('0' of '1') van de Bridge
                data = await reader.read(1024)
                if not data:
                    print("\n[!] Bridge heeft de verbinding verbroken.")
                    break
                
                message = data.decode('utf-8')
                
                # Stuur de data door naar alle actieve browsers
                for ws in list(WS_CLIENTS):
                    try:
                        await ws.send_str(message)
                    except Exception as e:
                        print(f"Fout bij sturen naar browser: {e}")

        except (ConnectionRefusedError, OSError):
            # Geen bridge gevonden? Wacht 2 seconden en probeer opnieuw
            print(".", end="", flush=True)
            await asyncio.sleep(2)
        except Exception as e:
            print(f"\n[Fout] Onverwachte fout in bridge_client: {e}")
            await asyncio.sleep(2)
        finally:
            if writer:
                writer.close()
                try:
                    await writer.wait_closed()
                except:
                    pass

async def init_app():
    """Initialiseert de webserver"""
    app = web.Application()
    app.router.add_get('/ws', websocket_handler)
    # Serveer statische bestanden (je index.html en arduino_uno.png)
    app.router.add_static('/static', './static')
    
    # Homepage redirect naar index.html
    async def index(request):
        return web.FileResponse('./static/index.html')
    app.router.add_get('/', index)
    
    return app

async def main():
    app = await init_app()
    runner = web.AppRunner(app)
    await runner.setup()
    site = web.TCPSite(runner, WEB_HOST, WEB_PORT)
    
    # Start de webserver en de bridge-client tegelijkertijd
    await asyncio.gather(
        site.start(),
        bridge_client_task()
    )
    
    print(f"\nWebserver draait op http://localhost:{WEB_PORT}")
    
    # Houd de loop draaiende
    while True:
        await asyncio.sleep(3600)

if __name__ == '__main__':
    try:
        asyncio.run(main())
    except KeyboardInterrupt:
        print("\nServer gestopt.")

