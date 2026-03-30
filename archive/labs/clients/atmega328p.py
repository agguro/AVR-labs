#!/usr/bin/env python3
import asyncio
import sys
from aiohttp import web

# Global set to keep track of active browser connections
WS_CLIENTS = set()

async def websocket_handler(request):
    """Manages WebSocket communication with the browser."""
    ws = web.WebSocketResponse()
    await ws.prepare(request)
    
    WS_CLIENTS.add(ws)
    try:
        async for msg in ws:
            if msg.type == web.WSMsgType.TEXT and msg.data == 'close':
                await ws.close()
    finally:
        WS_CLIENTS.remove(ws)
        
    return ws

async def bridge_client_task(bridge_port):
    """Acts as a client connecting to the C-Bridge server."""
    print(f"[Python] Connecting to Bridge on port {bridge_port}...")
    
    while True:
        writer = None
        try:
            # Connect to the local C-Bridge server
            reader, writer = await asyncio.open_connection('127.0.0.1', bridge_port)
            print(f"\n[OK] Connected to Bridge (Port {bridge_port})")

            while True:
                data = await reader.read(1024)
                if not data:
                    print(f"\n[!] Connection to Bridge {bridge_port} lost.")
                    break
                
                # Broadcast the received '0' or '1' to all connected browsers
                message = data.decode('utf-8')
                for ws in list(WS_CLIENTS):
                    try:
                        await ws.send_str(message)
                    except:
                        pass # WebSocket might have closed during iteration

        except (ConnectionRefusedError, OSError):
            # If bridge is not running, wait and try again
            print(".", end="", flush=True)
            await asyncio.sleep(2)
        finally:
            if writer:
                writer.close()
                await asyncio.sleep(0.1)

async def init_app():
    """Sets up the web routes."""
    app = web.Application()
    app.router.add_get('/ws', websocket_handler)
    # Serves the HTML and images from the /static folder
    app.router.add_static('/static', './static')
    
    # Redirect base URL to index.html
    async def index(request):
        return web.FileResponse('./static/index.html')
    app.router.add_get('/', index)
    
    return app

async def main():
    # 1. Parse command line arguments
    if len(sys.argv) < 3:
        print(f"Usage: {sys.argv[0]} <bridge_port> <web_port>")
        print(f"Example: {sys.argv[0]} 9999 8000")
        sys.exit(1)

    bridge_port = int(sys.argv[1])
    web_port = int(sys.argv[2])

    # 2. Start the web server and bridge client concurrently
    app = await init_app()
    runner = web.AppRunner(app)
    await runner.setup()
    site = web.TCPSite(runner, '0.0.0.0', web_port)
    
    print(f"Web Dashboard: http://localhost:{web_port}")
    
    await asyncio.gather(
        site.start(),
        bridge_client_task(bridge_port)
    )

if __name__ == '__main__':
    try:
        asyncio.run(main())
    except KeyboardInterrupt:
        print("\nServer stopped.")
