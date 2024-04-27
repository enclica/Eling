function generateHTMLPage(packageJson,configJson) {
  
    const navbarLinks = configJson.navbar.map(link => `<a href="${link.url}">${link.title}</a>`).join(' | ');
  
  
    return `
      <!DOCTYPE html>
      <html lang="en">
      <head>
        <meta charset="UTF-8">
        <meta name="viewport" content="width=device-width, initial-scale=1.0">
        <title>${packageJson.name} Info - Baton package manager</title>
        <link rel="stylesheet" href="https://unpkg.com/sakura.css/css/sakura-dark.css" type="text/css">
        <style>
        body {
          max-width: 70em;
        }
        
        nav {
          display: flex;
          justify-content: space-between;
        }
        input {
          width: 100%;
        }
        
        footer {
          border-top: 1px solid gray;
        }
        </style>      
  
        <header>
        <nav>
          <div>${configJson.sitename}</div>
  
          <div>
            ${navbarLinks}
          </div>
        </nav>
      </header>
      <body>
        <h1>${packageJson.name}</h1>
        <p><strong>Description:</strong> ${packageJson.description}</p>
        <p><strong>Version:</strong> ${packageJson.version}</p>
        <p><strong>Author:</strong> ${packageJson.author}</p>
        <ul>
          <strong>Downloads:</strong>
          ${packageJson.files.map(file => `<li><a href="/packages/${packageJson.name}/${file}">Download ${file}</a></li>`).join('')}
        <l>
  
        <script src="https://cdn.jsdelivr.net/npm/highlight.js"></script>
          <script>hljs.initHighlightingOnLoad();</script>
  
      <h1>Dependencies</h1>
      <ul>
        ${Object.keys(packageJson.dependencies).map(dep => `<li>${dep}</li>`).join('')}
      </ul>
  
      <h1>Eling Version support</h1>
      <ul>
        ${Object.keys(packageJson.eling).map(eling => `<li>${eling}</li>`).join('')}
      </ul>

      <h1> keywords </h1>
        <ul>
            ${packageJson.keywords.map(keyword => `<li>${keyword}</li>`).join('')}
        </ul>

      <h1>Baton install command</h1>
        <pre><code>baton install ${packageJson.name}</code></pre>
  
      <h2>Package JSON raw</h2>
      <pre><code>${generateJSONFile(packageJson)}</code></pre>
  
      </body>
      </html>
    `;
  }


  function generatesearchpageHTMLPage(jsonpackages,configJson) {
        //generate a html page with a search bar and a list of packages with their name and description and when clicked on the name it will redirect to the package page
        const navbarLinks = configJson.navbar.map(link => `<a href="${link.url}">${link.title}</a>`).join(' | ');
        return `
        <!DOCTYPE html>
        <html lang="en">
        
        <head>
          <meta charset="UTF-8">
          <meta name="viewport" content="width=device-width, initial-scale=1.0">
          <title>${configJson.sitename}</title>
          <link rel="stylesheet" href="https://unpkg.com/sakura.css/css/sakura-dark.css" type="text/css">
          <style>
          body {
            max-width: 70em;
          }
          
          nav {
            display: flex;
            justify-content: space-between;
          }
          input {
            width: 100%;
          }
          
          footer {
            border-top: 1px solid gray;
          }
          </style>      
        
          <header>
          <nav>
            <div>${configJson.sitename}</div>
        
            <div>
              ${navbarLinks}
            </div>
          </nav>
        </header>

        <body>
          <h1>${configJson.sitename}</h1>
          <form action="/search" method="get">
            <input type="text" name="q" placeholder="Search packages">
            <input type="submit" value="Search">
          </form>
          <ul>
            ${jsonpackages.map(packageJson => `<li><a href="/packages/${packageJson.name}">${packageJson.name}</a> - ${packageJson.description}</li>`).join('')}
          </ul>
        </body>
        </html>
        `;


        }
        function generatenosearchpageHTMLPage(configJson) {
          //generate a html page with a search bar and a list of packages with their name and description and when clicked on the name it will redirect to the package page
          const navbarLinks = configJson.navbar.map(link => `<a href="${link.url}">${link.title}</a>`).join(' | ');
          return `
          <!DOCTYPE html>
          <html lang="en">
          
          <head>
            <meta charset="UTF-8">
            <meta name="viewport" content="width=device-width, initial-scale=1.0">
            <title>${configJson.sitename}</title>
            <link rel="stylesheet" href="https://unpkg.com/sakura.css/css/sakura-dark.css" type="text/css">
            <style>
            body {
              max-width: 70em;
            }
            
            nav {
              display: flex;
              justify-content: space-between;
            }
            input {
              width: 100%;
            }
            
            footer {
              border-top: 1px solid gray;
            }
            </style>      
          
            <header>
            <nav>
              <div>${configJson.sitename}</div>
          
              <div>
                ${navbarLinks}
              </div>
            </nav>
          </header>
  
          <body>
            <h1>${configJson.sitename}</h1>
            <form action="/search" method="get">
              <input type="text" name="q" placeholder="Search packages">
              <input type="submit" value="Search">
            </form>
            <ul>
              <h1>No search results found</h1>
            </ul>
          </body>
          </html>
          `;
  
  
          }

          function generateHTMLPagedefaultpackages(packageList,configJson) {
            const navbarLinks = configJson.navbar.map(link => `<a href="${link.url}">${link.title}</a>`).join(' | ');
            return `
            <!DOCTYPE html>
            <html lang="en">
            
            <head>
              <meta charset="UTF-8">
              <meta name="viewport" content="width=device-width, initial-scale=1.0">
              <title>${configJson.sitename}</title>
              <link rel="stylesheet" href="https://unpkg.com/sakura.css/css/sakura-dark.css" type="text/css">
              <style>
              body {
                max-width: 70em;
              }
              
              nav {
                display: flex;
                justify-content: space-between;
              }
              input {
                width: 100%;
              }
              
              footer {
                border-top: 1px solid gray;
              }
              </style>      
            
              <header>
              <nav>
                <div>${configJson.sitename}</div>
            
                <div>
                  ${navbarLinks}
                </div>
              </nav>
            </header>
    
            <body>



              <ul>
                ${packageList.map(packageJson => `<li><a href="/packages/${packageJson.name}">${packageJson.name}</a> - ${packageJson.description}</li>`).join('')}
              </ul>

            </body>

            </html>
            `;
          }
  function generateJSONFile(packageJson) {
    return JSON.stringify(packageJson, null, 2);
    }


  module.exports = { generateHTMLPage, generatesearchpageHTMLPage,generatenosearchpageHTMLPage,generateHTMLPagedefaultpackages};