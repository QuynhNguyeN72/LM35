const char html_page[] PROGMEM = R"rawString(
<!DOCTYPE html>
<html>
    <head>
        <title>Homepage</title>
        <meta charset="UTF-8" />
        <meta name="viewport" content="width=device-width, initial-scale=1.0" />
        <style>

            .ul {
                list-style-type: none;
                margin: 0;
                padding: 0;
              }

            #logo {
                display: flex;
                justify-content: space-between;
                font-family: 'Arial', sans-serif;
            }

            .home li {
                display: inline;
                margin-left: 10px;
                margin-right: 15px;
                font-family: 'Arial', sans-serif;
              }
              
            .home li a {
                text-decoration: none;
                color: black;
                font-weight: bold;
                font-size: larger;
              }
              
            .home li a:hover {
                color: pink;
              }

            .infor h1 {
                font-size: 100%;
                color: black;
                margin-bottom: 20px;
            }

            .infor li {
                margin: 10px;
            }
            .infor {
                margin-right: 30px;
            }

            .body-info {
                display: flex;
                justify-content: space-between;
                font-family: 'Arial', sans-serif;
                align-items: center;
                margin: auto;
                text-align: center;
                font-weight: bold;
            }
    
            .doC {
                background-color: lightblue;
                margin: 200px;
                border-radius: 5%;
                height: 100%; 
                width: 100%; 
            }

            .doF {
                background-color: lightpink;
                margin: 200px;
                border-radius: 5%;
                height: 100%; 
                width: 100%; 
            }

            .degree-symbol {
                font-size: 200%;
                display: flex;
                align-items: baseline;
                justify-content: center
              }
            
        </style>
    </head>
<body>
    <header>

        <div id = "logo">
            <img src="https://raw.githubusercontent.com/QuynhNguyeN72/LM35/main/FETEL.HCMUS.png" alt="FETEL-Logo" width="30%" height="20%">

            <ul class = "infor">
                <h1>Thành viên nhóm</h1>
                <li>21200138 - Lê Văn Minh</li>
                <li>21200196 - Nguyễn Thị Phương Quỳnh</li>
            </ul>
        </div>

        <div class = "headbar">
            <ul class = "home">
                <li><a href="https://github.com/QuynhNguyeN72/LM35">Source code</a></li>
            </ul>
        </div>

    </header>
    <main>
        <h1 style="text-align: center; font-family: 'Arial', sans-serif;"> ESP32 LM35 Temperature</h1>
        <div class = "body-info">
            <div class = "doC">
                <h2>Độ C đo được</h2>
                <span class="degree-symbol">
                    <span id="doC_nhietdo">--</span> &deg;C
                </span>
            </div>

            <div class = "doF">
                <h2>Độ F đo được</h2>
                <span class="degree-symbol">
                    <span id="doF_nhietdo">--</span> &deg;F
                </span>
            </div>
        </div>
    </main>

    <script>
        setInterval(function() {
          var xhttp = new XMLHttpRequest();
          xhttp.onreadystatechange = function() {
            if (this.readyState == 4 && this.status == 200) {
              var data = JSON.parse(this.responseText);
              document.getElementById("doC_nhietdo").innerHTML = data.celsius;
              document.getElementById("doF_nhietdo").innerHTML = data.fahrenheit;
            }
          };
          xhttp.open("GET", "readTemp", true);
          xhttp.send();
        }, 1000);
    </script>
</body>
</html>
)rawString";