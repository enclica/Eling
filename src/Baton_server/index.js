const express = require('express');
const fs = require('fs').promises;
const path = require('path');
const app = express();
const port = 3000;

app.get('/packages/:packageName', async (req, res) => {
  const packageName = req.params.packageName;
  const packagePath = path.join(__dirname, 'packages', packageName, 'package.json');

  try {
    const packageData = await fs.readFile(packagePath, 'utf8');
    const packageJson = JSON.parse(packageData);

    // Respond differently based on the "Accept" header
    if (req.accepts('html')) {
      res.type('html').send(generateHTMLPage(packageJson));
    } else {
      res.json(packageJson);
    }
  } catch (error) {
    res.status(404).send(`Package not found: ${packageName}`);
  }
});

function generateHTMLPage(packageJson) {
  return `
    <!DOCTYPE html>
    <html lang="en">
    <head>
      <meta charset="UTF-8">
      <meta name="viewport" content="width=device-width, initial-scale=1.0">
      <title>${packageJson.name} Info</title>
    </head>
    <body>
      <h1>${packageJson.name}</h1>
      <p><strong>Description:</strong> ${packageJson.description}</p>
      <p><strong>Version:</strong> ${packageJson.version}</p>
      <ul>
        <strong>Downloads:</strong>
        ${packageJson.files.map(file => `<li><a href="${file}">Download</a></li>`).join('')}
      </ul>
    </body>
    </html>
  `;
}

function generateJSONFile(packageJson) {
    return JSON.stringify(packageJson, null, 2);
    }
    

app.listen(port, () => {
  console.log(`Server running at http://localhost:${port}/`);
  //list first 5 packages
    fs.readdir(path.join(__dirname, 'packages'))
        .then(packages => {
        console.log('Available packages:');
        packages.slice(0, 5).forEach(packageName => {
            console.log(`- ${packageName} (http://localhost:${port}/packages/${packageName})`);
        });
        });
});
