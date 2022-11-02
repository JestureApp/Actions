const {platform, arch} = process;

// load correct binary
if (! platform in ['darwin', 'win32', 'linux']) {
	throw new Error('Unsupported platform : ${platform}');
}
else if (arch != 'x64') {
	throw new Error(`Unsupported architecture: ${arch}`);
}

let libc = {'darwin': '', 'win32': '-msvc', 'linux': '-gnu'}[platform];

module.exports = require(`@jesture/keystrokes-${platform}-${arch}${libc}`);