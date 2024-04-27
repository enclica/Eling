const express = require('express');
const fs = require('fs').promises;
const path = require('path');
const { config } = require('process');
const { generateHTMLPage,generatenosearchpageHTMLPage, generatesearchpageHTMLPage,generateHTMLPagedefaultpackages } = require('./pages');
const app = express();
const port = 3000;

//allow downloading of files from packages
app.use('/packages', express.static(path.join(__dirname, 'packages')));
app.use(express.static('public'));


//change any html from the public folder with anything with ${} to its value
app.get('/public/:filename', async (req, res) => {
  const filename = req.params.filename;
  const filePath = path.join(__dirname, 'public', filename);
  const fileContent = await fs.readFile
  (filePath, 'utf8');
  const configPath = path.join(__dirname, 'config', 'batonpm.json');
  const configData =  await fs.readFile(configPath);
  const configJson = JSON.parse(configData);
  const replacedContent = fileContent.replace(/\${(.*?)}/g, (match, key) => {
    return configJson[key] || '';
  });
  res.type('html').send(replacedContent);
});







//search packages with a search bar and find packages with their name and description and base it off the keywords in the bpackage.json of each package
app.get('/search', async (req, res) => {
  console.log("searching");
  const packagesDir = path.join(__dirname, 'packages');
  const packages = await fs.readdir(packagesDir);
  const jsonpackages = [];
  const searchQuery = req.query.q; // Get the search query from the request query parameters
  for (const packageName of packages) {
    const packagePath = path.join(packagesDir, packageName, 'bpackage.json');
    const packageJson = await fs.readFile(packagePath);
    const packjson = JSON.parse(packageJson);
    // Check if the package name or description contains the search query
    if (packjson.name.includes(searchQuery) || packjson.description.includes(searchQuery)) {
      // Check if the package keywords contain the search query
      if (packjson.keywords.includes(searchQuery)) {
        jsonpackages.push(packjson);
      }
    }
  }
  //get config file in config/batonpm.json
  const configPath = path.join(__dirname, 'config', 'batonpm.json');
  const configData =  await fs.readFile(configPath);
  const configJson = JSON.parse(configData);
  if (jsonpackages.length === 0) {
    if (req.accepts('html')) {
      res.type('html').send(generatenosearchpageHTMLPage(configJson));
    } else {
      res.json([]);
    }
  } else {
    if (req.accepts('html')) {
      res.type('html').send(generatesearchpageHTMLPage(jsonpackages,configJson));
    } else {
      res.json(jsonpackages);
    }
  }
});
app.get('/packages/', async (req, res) => {
  const configPath = path.join(__dirname, 'config', 'batonpm.json');
  const configData =  await fs.readFile(configPath);
  const configJson = JSON.parse(configData);
  const packagesDir = path.join(__dirname, 'packages');
  const packages = await fs.readdir(packagesDir);
  const packageList = [];
  for (let i = 0; i < 30 && i < packages.length; i++) {
    const packageName = packages[i];
    const packagePath = path.join(packagesDir, packageName, 'bpackage.json');
    const packageJson = await fs.readFile(packagePath);
    const packjson = JSON.parse(packageJson);
    packageList.push(packjson);
  }
  if(req.accepts('html')){
    res.type('html').send(generateHTMLPagedefaultpackages(packageList,configJson));
  }else{
  res.json(packageList);
  }
});
app.get('/packages/:packageName', async (req, res) => {
  const packageName = req.params.packageName;
  const packagePath = path.join(__dirname, 'packages', packageName, 'bpackage.json');
  const packageJson = await fs.readFile(packagePath);
  const packjson = JSON.parse(packageJson);
       //get config file in config/batonpm.json
       const configPath = path.join(__dirname, 'config', 'batonpm.json');
       const configData =  await fs.readFile(configPath);
       const configJson = JSON.parse(configData);
  try {
    if (req.accepts('html')) {
      res.type('html').send(generateHTMLPage(packjson,configJson));
    } else {
      res.json(packjson);
    }
  } catch (error) {
    console.error("\x1b[31m"+error+"\x1b[0m");
    res.status(404).send(`<html><head><link rel="stylesheet" href="https://unpkg.com/sakura.css/css/sakura-dark.css" type="text/css"></head><body>Package not found: ${packageName}</body></html>`);
  }
});


app.listen(port, () => {
  console.log(`Server running at http://localhost:${port}/`);
  //list first 5 packages
});
