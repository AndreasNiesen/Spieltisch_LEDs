#ifndef WEB_PAGE_H
#define WEB_PAGE_H

#include <Arduino.h>

const String webpage = R"(<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <meta http-equiv="X-UA-Compatible" content="IE=edge">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>LED Control Center</title>

    <style>
        *, *::before, *::after {
            margin: 0;
            padding: 0;
            box-sizing: border-box;
        }

        body {
            width: 100vw;
            height: 100vh;
            display: grid;
            place-items: center;
        }

        .cmdBtn {
            color: black;
            background-color: aquamarine;
            padding: 5px 10px;
            border-radius: 100vw;
        }
    </style>

    

</head>
<body>
    <button class="cmdBtn" id="cmd1">CMD 1</button>
    <button class="cmdBtn" id="cmd2">CMD 2</button>
    <button class="cmdBtn" id="cmd3">CMD 3</button>

    <script>
        console.log("hi");
        let cmdBtnArray = document.getElementsByClassName("cmdBtn");

        for(btn of cmdBtnArray) {
            btn.addEventListener('click', e => {
                fetch('/' + e.target.id, {
                    method: 'POST',
                    headers: {
                        'Content-Length': '0',
                    },
                })
                .then(response => response.json())
                .then(response => console.log(JSON.stringify(response)));
            });
        }
    </script>
</body>
</html>)";

#endif