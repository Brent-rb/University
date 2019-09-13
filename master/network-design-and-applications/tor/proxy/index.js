const proxy_fallback_port = 8000
const client_fallback_port = 5000
const client_location = 'localhost'

var httpProxy = require('http-proxy')
const argv = require('yargs')
        .default('p', proxy_fallback_port)
        .default('c', client_fallback_port)
        .alias('c', 'client_port')
        .alias('p', 'proxy_port')
        .argv

var proxy_options = {
    target: {
        host: client_location,
        port: argv.client_port,
    },
    toProxy: true,
}

var proxy = httpProxy.createProxyServer(proxy_options)

proxy.on('error', function(err, req, res) {
    console.error(err)
    res.writeHead(500, {
        'Content-Type': 'text/html'
    })

    res.end('Internal server error!')
})

proxy.on('proxyReq', function(proxyReq, req, res, options) {
    // console.log(proxyReq)
    proxyReq.path = '/getResource?URL=' + proxyReq.path
    console.log("Updated path url to %s", proxyReq.path)
})

console.log("Client at http://%s:%s", client_location, argv.client_port)
console.log("Proxy at http://%s:%s", 'localhost', argv.proxy_port)
proxy.listen(argv.proxy_port)