const fs = require('fs');
const path = require('path');

const packageJson = JSON.parse(fs.readFileSync(path.join(__dirname, './../../../package.json')));

const today = new Date();
const dateString = `${today.getFullYear()}.${today.getMonth()+1}.${today.getDate()}`;

packageJson.binary.remote_path = packageJson.binary.remote_path.replace(/{version}/, `nightly/${dateString}`);

fs.writeFile(path.join(__dirname, './../../../package.json'), JSON.stringify(packageJson), (err)=>{
  if (err) return console.log('err');
  console.log('saved file');
})