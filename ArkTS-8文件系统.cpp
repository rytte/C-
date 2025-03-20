
//访问系统文件

//通过URI访问
let uri = fileuri.getUriFromPath('/sys/class/thermal/thermal_zone0/temp')
console.warn(uri);
let val: Uint8Array = new Uint8Array(1024 * 1024)
let fileTarget = fs.openSync(uri, fs.OpenMode.READ_ONLY)
fs.readSync(fileTarget.fd, val.buffer as ArrayBuffer);
const textDecoder: util.TextDecoder = util.TextDecoder.create('utf-8');
let decodedString = textDecoder.decode(val);
console.warn(decodedString)
console.warn(fileTarget.path)

//直接访问
let str = fs.readTextSync('/sys/class/thermal/thermal_zone0/temp')
console.warn(str);