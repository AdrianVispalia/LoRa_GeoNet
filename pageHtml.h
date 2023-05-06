#ifndef _PAGE_HTML_H
#define _PAGE_HTML_H
const char index_html[] PROGMEM =  "<!DOCTYPE HTML>\n\ 
<html>\n\ 
\n\ 
<head>\n\ 
    <link rel=\"icon\" href=\"../Telegram_Logo.svg\">\n\ 
    <title>LoRa GeoNet</title>\n\ 
    <meta name=\"viewport\" content=\"width=device-width, initial-scale=1, maximum-scale=1\">\n\ 
    <style>\n\ 
         :root {\n\ 
            --placeholder-color: #d4d3d3a3;\n\ 
        }\n\ 
        \n\ 
        body {\n\ 
            margin: 0;\n\ 
        }\n\ 
        \n\ 
        div {\n\ 
            width: auto;\n\ 
            word-break: break-word;\n\ 
            text-align: left;\n\ 
        }\n\ 
        \n\ 
        @-webkit-keyframes animation-online {\n\ 
            0% {\n\ 
                background-position: 0% 0%\n\ 
            }\n\ 
            100% {\n\ 
                background-position: 100% 100%\n\ 
            }\n\ 
        }\n\ 
        \n\ 
        @-moz-keyframes animation-online {\n\ 
            0% {\n\ 
                background-position: 0% 0%\n\ 
            }\n\ 
            100% {\n\ 
                background-position: 100% 100%\n\ 
            }\n\ 
        }\n\ 
        \n\ 
        @keyframes animation-online {\n\ 
            0% {\n\ 
                background-position: 0% 0%\n\ 
            }\n\ 
            100% {\n\ 
                background-position: 100% 100%\n\ 
            }\n\ 
        }\n\ 
        \n\ 
        @-webkit-keyframes animation-offline {\n\ 
            0% {\n\ 
                background-position: 100% 100%\n\ 
            }\n\ 
            100% {\n\ 
                background-position: 0% 0%\n\ 
            }\n\ 
        }\n\ 
        \n\ 
        @-moz-keyframes animation-offline {\n\ 
            0% {\n\ 
                background-position: 100% 100%\n\ 
            }\n\ 
            100% {\n\ 
                background-position: 0% 0%\n\ 
            }\n\ 
        }\n\ 
        \n\ 
        @keyframes animation-offline {\n\ 
            0% {\n\ 
                background-position: 100% 100%\n\ 
            }\n\ 
            100% {\n\ 
                background-position: 0% 0%\n\ 
            }\n\ 
        }\n\ 
        \n\ 
        .online {\n\ 
            -webkit-animation: animation-online 2s ease;\n\ 
            -moz-animation: animation-online 2s ease;\n\ 
            animation: animation-online 2s ease;\n\ 
            animation-fill-mode: forwards;\n\ 
        }\n\ 
        \n\ 
        .offline {\n\ 
            -webkit-animation: animation-offline 2s ease;\n\ 
            -moz-animation: animation-offline 2s ease;\n\ 
            animation: animation-offline 2s ease;\n\ 
            animation-fill-mode: forwards;\n\ 
        }\n\ 
        \n\ 
        #main-frame {\n\ 
            top: 0;\n\ 
            left: 0;\n\ 
            height: 100vh;\n\ 
            background: linear-gradient(122.5deg, rgba(224, 2, 2, 1), rgba(255, 141, 0, 1), rgba(254, 255, 0, 1), rgba(29, 197, 217, 1), rgba(35, 61, 190, 1), rgba(157, 4, 167, 1));\n\ 
            background-size: 300% 300%;\n\ 
        }\n\ 
        \n\ 
        .chat {\n\ 
            position: relative;\n\ 
            overflow: hidden;\n\ 
            margin-right: auto;\n\ 
            margin-left: auto;\n\ 
            top: 10%;\n\ 
            width: 50%;\n\ 
            height: 80%;\n\ 
            min-width: 340px;\n\ 
            background-color: rgba(0, 0, 0, 0.5);\n\ 
            color: white;\n\ 
            border-radius: 20px;\n\ 
            -webkit-animation: bounce-animation .6s ease-in-out;\n\ 
            -moz-animation: bounce-animation .6s ease-in-out;\n\ 
            animation: bounce-animation .6s ease-in-out;\n\ 
        }\n\ 
        \n\ 
        @media(max-width: 480px) {\n\ 
            .chat {\n\ 
                top: 2%;\n\ 
                width: 90%;\n\ 
                height: 86%;\n\ 
            }\n\ 
        }\n\ 
        \n\ 
        .chat-title {\n\ 
            /* height: 6.5%; */\n\ 
            padding: 0.8vh;\n\ 
            padding-left: 2.2vh;\n\ 
            background: rgba(0, 0, 0, 0.2);\n\ 
        }\n\ 
        \n\ 
        .chat-title h1 {\n\ 
            margin: 0;\n\ 
            text-align: center;\n\ 
            font-family: Georgia, serif;\n\ 
            color: #ffffffc0;\n\ 
        }\n\ 
        \n\ 
        .target-container {\n\ 
            padding: 0.8vh;\n\ 
            padding-left: 2.2vh;\n\ 
            background: rgba(0, 0, 0, 0.15);\n\ 
            display: flex;\n\ 
            padding: 1.8%;\n\ 
            padding-left: 3%;\n\ 
            padding-right: 3%;\n\ 
            align-items: center;\n\ 
            place-content: space-between;\n\ 
        }\n\ 
        \n\ 
        .target-container h2 {\n\ 
            margin: 0;\n\ 
            text-align: left;\n\ 
            font-family: Georgia, serif;\n\ 
            color: #ffffffc0;\n\ 
            display: inline;\n\ 
        }\n\ 
        \n\ 
        .target-form {\n\ 
            display: contents;\n\ 
        }\n\ 
        \n\ 
        .target-container label {\n\ 
            margin: 0;\n\ 
            font-family: Georgia, serif;\n\ 
            color: #ffffffc0;\n\ 
            padding: 0.5%;\n\ 
        }\n\ 
        \n\ 
        .target-container input {\n\ 
            background: rgba(255, 255, 255, 0.427);\n\ 
            border-radius: 4px;\n\ 
            width: 12%;\n\ 
        }\n\ 
        \n\ 
        @media(max-width: 730px) {\n\ 
            .target-container input {\n\ 
                width: 10%;\n\ 
            }\n\ 
        }\n\ 
        \n\ 
         ::-webkit-scrollbar {\n\ 
            width: 7px;\n\ 
        }\n\ 
        \n\ 
         ::-webkit-scrollbar-track {\n\ 
            background: rgba(0, 0, 0, 0);\n\ 
        }\n\ 
        \n\ 
         ::-webkit-scrollbar-thumb {\n\ 
            background: rgba(0, 0, 0, 0.28);\n\ 
            border-radius: 75vh;\n\ 
        }\n\ 
        \n\ 
         ::-webkit-scrollbar-thumb:hover {\n\ 
            background: rgba(0, 0, 0, 0.44);\n\ 
            width: 8px;\n\ 
        }\n\ 
        \n\ 
        .messages {\n\ 
            /* height: 60vh; */\n\ 
            height: 83%;\n\ 
            overflow: auto;\n\ 
            margin: 1.5%;\n\ 
            margin-top: 0%;\n\ 
            margin-bottom: 0%;\n\ 
            padding-left: 2%;\n\ 
            padding-right: 2%;\n\ 
        }\n\ 
        \n\ 
        @media(max-width: 1100px) {\n\ 
            .messages {\n\ 
                height: 81.5%;\n\ 
            }\n\ 
        }\n\ 
        \n\ 
        .messages-content {\n\ 
            width: auto;\n\ 
            height: auto;\n\ 
        }\n\ 
        \n\ 
        .messages .message .avatar img {\n\ 
            width: 100%;\n\ 
            height: auto;\n\ 
        }\n\ 
        \n\ 
        .message {\n\ 
            width: fit-content;\n\ 
            width: -moz-fit-content;\n\ 
            padding: 1.5%;\n\ 
            padding-top: 0.55%;\n\ 
            padding-bottom: 0.55%;\n\ 
            margin-top: 1.6%;\n\ 
            display: block;\n\ 
            color: #fff;\n\ 
            text-align: right;\n\ 
            background: rgba(0, 0, 0, 0.3);\n\ 
            border-radius: 10px 10px 10px 0;\n\ 
            color: rgba(255, 255, 255, 0.5);\n\ 
            max-width: 72%;\n\ 
        }\n\ 
        \n\ 
        .new-message {\n\ 
            -webkit-animation: bounce-animation .4s ease-in-out;\n\ 
            -moz-animation: bounce-animation .4s ease-in-out;\n\ 
            animation: bounce-animation .4s ease-in-out;\n\ 
        }\n\ 
        \n\ 
        @media(max-width: 1100px) {\n\ 
            .message {\n\ 
                padding: 2.5%;\n\ 
                padding-top: 1.7%;\n\ 
                padding-bottom: 1.7%;\n\ 
                margin-top: 2.6%;\n\ 
                max-width: 82%;\n\ 
            }\n\ 
        }\n\ 
        \n\ 
        .message-personal {\n\ 
            margin-left: auto;\n\ 
            margin-right: 0.3%;\n\ 
            border-radius: 10px 10px 0 10px;\n\ 
            color: white;\n\ 
            background: linear-gradient(122.5deg, #ff0000, rgba(255, 128, 0, 1), #319ac9, #364eb6);\n\ 
            background-size: 300% 300%;\n\ 
        }\n\ 
        \n\ 
        .message-box {\n\ 
            position: absolute;\n\ 
            bottom: 0;\n\ 
            width: -webkit-fill-available;\n\ 
            padding-bottom: 2.5%;\n\ 
            padding-left: 4%;\n\ 
            padding-right: 4%;\n\ 
            padding-top: 3%;\n\ 
            background: linear-gradient(122.5deg, rgb(98 38 0), rgb(101 51 0), rgb(102 72 0), rgb(20 22 74), rgb(32 16 72), rgb(47 8 70));\n\ 
            background-size: 300% 300%;\n\ 
        }\n\ 
        \n\ 
        .message-box .message-input {\n\ 
            height: 1.2em;\n\ 
        }\n\ 
        \n\ 
        textarea {\n\ 
            border: none;\n\ 
            overflow: auto;\n\ 
            outline: none;\n\ 
            -webkit-box-shadow: none;\n\ 
            -moz-box-shadow: none;\n\ 
            box-shadow: none;\n\ 
            resize: none;\n\ 
        }\n\ 
        \n\ 
        textarea::placeholder {\n\ 
            color: var(--placeholder-color);\n\ 
        }\n\ 
        \n\ 
        textarea:-ms-input-placeholder {\n\ 
            color: var(--placeholder-color);\n\ 
        }\n\ 
        \n\ 
        textarea::-ms-input-placeholder {\n\ 
            color: var(--placeholder-color);\n\ 
        }\n\ 
        \n\ 
        .message-input {\n\ 
            color: #ffffff;\n\ 
            padding: 1%;\n\ 
            padding-left: 2%;\n\ 
            border-radius: 0.7vw;\n\ 
            width: 78%;\n\ 
            background: linear-gradient(122.5deg, #bc2b2b45, #85701c3d, #233fbe45, #651eb23d);\n\ 
            background-size: 300% 300%;\n\ 
        }\n\ 
        \n\ 
        @keyframes online-input-animation {\n\ 
            0% {\n\ 
                width: 78%;\n\ 
                background-position: 0% 0%;\n\ 
            }\n\ 
            100% {\n\ 
                width: 85%;\n\ 
                background-position: 100% 100%;\n\ 
            }\n\ 
        }\n\ 
        \n\ 
        @keyframes offline-input-animation {\n\ 
            0% {\n\ 
                width: 85%;\n\ 
                background-position: 100% 100%;\n\ 
            }\n\ 
            100% {\n\ 
                width: 78%;\n\ 
                background-position: 0% 0%;\n\ 
            }\n\ 
        }\n\ 
        \n\ 
        .online.message-input {\n\ 
            -webkit-animation: online-input-animation 2s ease;\n\ 
            -moz-animation: online-input-animation 2s ease;\n\ 
            animation: online-input-animation 2s ease;\n\ 
            animation-fill-mode: forwards;\n\ 
            animation-delay: 400ms;\n\ 
        }\n\ 
        \n\ 
        .offline.message-input {\n\ 
            -webkit-animation: offline-input-animation 2s ease;\n\ 
            -moz-animation: offline-input-animation 2s ease;\n\ 
            animation: offline-input-animation 2s ease;\n\ 
            animation-fill-mode: forwards;\n\ 
        }\n\ 
        \n\ 
        .message-box .message-submit {\n\ 
            border-radius: 55%;\n\ 
            background: transparent;\n\ 
            cursor: pointer;\n\ 
            padding: 0px 0px;\n\ 
            /* width: 5%; */\n\ 
            float: right;\n\ 
        }\n\ 
        \n\ 
        .online.message-submit:hover {\n\ 
            background: #233dbe;\n\ 
            box-shadow: 0px 0px 2px 4px rgba(35, 61, 190, 0.8);\n\ 
        }\n\ 
        \n\ 
        .offline.message-submit:hover {\n\ 
            background: #b2491e;\n\ 
            box-shadow: 0px 0px 2px 4px rgb(202 44 0 / 83%);\n\ 
        }\n\ 
        \n\ 
        @keyframes appear {\n\ 
            0% {\n\ 
                color: rgba(255, 255, 255, 0);\n\ 
            }\n\ 
            100% {\n\ 
                color: rgba(255, 255, 255, 1);\n\ 
            }\n\ 
        }\n\ 
        \n\ 
        @keyframes disappear {\n\ 
            0% {\n\ 
                color: rgba(255, 255, 255, 1);\n\ 
            }\n\ 
            100% {\n\ 
                color: rgba(255, 255, 255, 0);\n\ 
            }\n\ 
        }\n\ 
        \n\ 
        .reconnect-appear {\n\ 
            animation: appear 300ms ease-in-out;\n\ 
            -webkit-transition: appear 300ms ease-in-out;\n\ 
            -ms-transition: appear 300ms ease-in-out;\n\ 
            animation-fill-mode: forwards;\n\ 
        }\n\ 
        \n\ 
        .reconnect-disappear {\n\ 
            animation: disappear 300ms ease-in-out;\n\ 
            -webkit-transition: disappear 300ms ease-in-out;\n\ 
            -ms-transition: disappear 300ms ease-in-out;\n\ 
            animation-fill-mode: forwards;\n\ 
        }\n\ 
        \n\ 
        #reconnect {\n\ 
            border-radius: 35%;\n\ 
            margin-right: 2.2%;\n\ 
            display: none;\n\ 
        }\n\ 
        \n\ 
        .rotation-class {\n\ 
            animation: rotate 600ms ease-in-out;\n\ 
            -webkit-transition: rotate 600ms ease-in-out;\n\ 
            -ms-transition: rotate 600ms ease-in-out;\n\ 
        }\n\ 
        \n\ 
        @keyframes rotate {\n\ 
            0% {\n\ 
                transform: rotate(0);\n\ 
            }\n\ 
            100% {\n\ 
                transform: rotate(360deg);\n\ 
            }\n\ 
        }\n\ 
        \n\ 
        @keyframes bounce-animation {\n\ 
            0% {\n\ 
                transform: scale(0.1);\n\ 
                transform: translateY(0.1, 0.2);\n\ 
            }\n\ 
            70% {\n\ 
                transform: scale(1.2);\n\ 
                transform: translateY(1, 1);\n\ 
            }\n\ 
            100% {\n\ 
                transform: scale(1);\n\ 
                transform: translateY(1, 1);\n\ 
            }\n\ 
        }\n\ 
        \n\ 
        .send-class {\n\ 
            animation: send-animation 1s ease-out;\n\ 
        }\n\ 
        \n\ 
        @keyframes send-animation {\n\ 
            0% {\n\ 
                transform: translateX(0%);\n\ 
            }\n\ 
            15% {\n\ 
                transform: translateX(-15%);\n\ 
            }\n\ 
            35% {\n\ 
                transform: translateX(25%);\n\ 
            }\n\ 
            100% {\n\ 
                transform: translateX(0%);\n\ 
            }\n\ 
        }\n\ 
    </style>\n\ 
</head>\n\ 
\n\ 
<body>\n\ 
    <div class=\"bg online\" id=\"main-frame\">\n\ 
        <div class=\"chat\">\n\ 
            <div class=\"chat-title\">\n\ 
                <h1>LoRa GeoNet</h1>\n\ 
            </div>\n\ 
            <div class=\"target-container\">\n\ 
                <h2>To:</h2>\n\ 
                <form class=\"target-form\">\n\ 
                    <label for=\"lat\">Latitude:</label>\n\ 
                    <input type=\"number\" id=\"latitude\" name=\"lat\" max=\"90.0\" min=\"-90.0\" value=\"0.0\">\n\ 
                    <label for=\"lon\">Longitude:</label>\n\ 
                    <input type=\"number\" id=\"longitude\" name=\"lon\" max=\"180.0\" min=\"-180.0\" value=\"0.0\">\n\ 
                </form>\n\ 
            </div>\n\ 
            <div class=\"messages\">\n\ 
                <div class=\"messages-content\" id=\"messages-container\"></div>\n\ 
            </div>\n\ 
            <div class=\"message-box online\" id=\"message-textarea-container\">\n\ 
                <textarea type=\"text\" class=\"message-input online\" id=\"message-textarea\" placeholder=\"Message\"></textarea>\n\ 
\n\ 
                <svg width=\"24\" height=\"24\" class=\"message-submit online\" id=\"send-message\">\n\ 
           <path fill=\"currentColor\" d=\"M 1.101 21.757 L 23.8 12.028 L 1.101 2.3 l 2.899 7.7 l 10.967 1.606 l -10.878 2.404 l -2.932 7.764 z\"></path>\n\ 
         </svg>\n\ 
                <svg width=\"26\" height=\"24\" class=\"message-submit offline\" id=\"reconnect\">\n\ 
           <path transform=\"scale(1, -1) translate(0, -24)\" fill=\"currentColor\"\n\ 
           d=\"M11.14.16c-2.9.4-5.56 2.22-7.04 4.8-.74 1.28-1.18 2.76-1.3 4.24l-.2 6.72h-2.8l5.38 7.52 4.02-7.52h-2.84q-.8-8.8 4.8-15.8z\n\ 
           M14.14 23.36c2.9-.4 5.56-2.22 7.04-4.8.74-1.28 1.18-2.76 1.3-4.24l.2-6.72h2.8l-5.38-7.52-4.02 7.52h2.84q.8 8.8-4.8 15.8z\"></path>\n\ 
         </svg>\n\ 
            </div>\n\ 
        </div>\n\ 
    </div>\n\ 
    <script>\n\ 
        /* WebSocket Section */\n\ 
        var gateway = 'ws://' + window.location.hostname + '/ws';\n\ 
        var websocket;\n\ 
\n\ 
        function initWebSocket() {\n\ 
            console.log('Trying to open a WebSocket connection...');\n\ 
            websocket = new WebSocket(gateway);\n\ 
            websocket.onopen = onOpen;\n\ 
            websocket.onclose = onClose;\n\ 
            websocket.onmessage = onMessage;\n\ 
            if (isOnline == false) changeStatus(false);\n\ 
        }\n\ 
\n\ 
        function onOpen(event) {\n\ 
            changeStatus(true);\n\ 
            console.log('Connection opened');\n\ 
        }\n\ 
\n\ 
        function onClose(event) {\n\ 
            changeStatus(false);\n\ 
            console.log('Connection closed');\n\ 
            setTimeout(initWebSocket, 2000); // try to reconnect */\n\ 
        }\n\ 
\n\ 
        function onMessage(event) {\n\ 
            console.log(\"onMessage\");\n\ 
            console.log(event);\n\ 
\n\ 
            if (event.data.length < 1) return;\n\ 
\n\ 
            switch (event.data[0]) {\n\ 
                case '1':\n\ 
                    addMsgToChat(event);\n\ 
                    break;\n\ 
                case '2':\n\ 
                    window.alert(event.data.split(\"|\")[1]);\n\ 
                    break;\n\ 
                default:\n\ 
                    console.log(\"Error onMessage unkown type:\");\n\ 
                    console.log(event);\n\ 
            }\n\ 
        }\n\ 
\n\ 
        /* Msg GUI & logic section */\n\ 
        function addMsgToChat(event) {\n\ 
            let messages_content = document.getElementById(\"messages-container\");\n\ 
            const node = document.createElement(\"div\");\n\ 
            node.classList.add(\"message\");\n\ 
            if (event.data.split(\"|\")[2] == username) {\n\ 
                node.innerHTML = event.data.split(\"|\")[3];\n\ 
                node.classList.add(\"message-personal\", \"online\");\n\ 
                document.getElementById(\"message-textarea\").value = \"\";\n\ 
            } else {\n\ 
                node.innerHTML = event.data.split(\"|\")[2] + ': ' + event.data.split(\"|\")[3];\n\ 
            }\n\ 
            messages_content.appendChild(node);\n\ 
            messages_content.scrollIntoView(false);\n\ 
        }\n\ 
\n\ 
        var reconnect_delay = window.innerWidth > 420 ? 400 : 1200;\n\ 
\n\ 
        function checkMsg(msg) {\n\ 
            if (msg.trim() == '') {\n\ 
                return false;\n\ 
            }\n\ 
\n\ 
            if (msg.length > 30 || msg.includes(\"|\")) {\n\ 
                alert(msg.length > 30 ? \"Error! Too many characters\" : \"Error! Msg shouldn't have '|' character\");\n\ 
                return false;\n\ 
            }\n\ 
\n\ 
            return true;\n\ 
        }\n\ 
\n\ 
        function sendMessage() {\n\ 
            let message = document.getElementById(\"message-textarea\").value;\n\ 
\n\ 
            if (checkMsg(message) == false) {\n\ 
                return;\n\ 
            }\n\ 
\n\ 
            websocket.send(\"1|\" +\n\ 
                String(document.getElementById(\"longitude\").value) + \",\" +\n\ 
                String(document.getElementById(\"latitude\").value) + \"|\" +\n\ 
                String(username) + \"|\" +\n\ 
                String(message));\n\ 
            document.getElementById(\"message-textarea\").value = \"\";\n\ 
            console.log(\"sent this through websocket: \" + message);\n\ 
\n\ 
            /*\n\ 
            let last = document.getElementById(\"messages-container\").lastElementChild;\n\ 
            last.classList.add('new-message');\n\ 
            setTimeout(\n\ 
                function() {\n\ 
                    last.classList.remove('new-message')\n\ 
                    last.classList.add(isOnline ? \"online\" : \"offline\");\n\ 
                    last.classList.remove(isOnline ? \"offline\" : \"online\");\n\ 
                },\n\ 
                1000);\n\ 
            */\n\ 
        }\n\ 
\n\ 
        /* Offline functinality */\n\ 
        function changeStatus(isOnline) {\n\ 
            reconnect_delay = window.innerWidth > 420 ? 400 : 1200;\n\ 
            console.log(\"changeStatus: \" + isOnline);\n\ 
\n\ 
            let elements = [document.getElementById(\"main-frame\"),\n\ 
                document.getElementById(\"message-textarea-container\"),\n\ 
                document.getElementById(\"message-textarea\"),\n\ 
                document.getElementById(\"send-message\")\n\ 
            ];\n\ 
            let messages_personal = document.getElementsByClassName(\"message-personal\");\n\ 
            let reconnect = document.getElementById(\"reconnect\");\n\ 
\n\ 
            let add_class = isOnline ? \"online\" : \"offline\";\n\ 
            let remove_class = isOnline ? \"offline\" : \"online\";\n\ 
\n\ 
            for (let element of elements) {\n\ 
                element.classList.remove(remove_class);\n\ 
                element.classList.add(add_class);\n\ 
            }\n\ 
\n\ 
            for (let msg of messages_personal) {\n\ 
                msg.classList.remove(remove_class);\n\ 
                msg.classList.add(add_class);\n\ 
            }\n\ 
\n\ 
            reconnect.classList.remove(\"rotation-class\");\n\ 
            if (isOnline == 1) {\n\ 
                reconnect.classList.remove(\"reconnect-appear\");\n\ 
                reconnect.classList.add(\"reconnect-disappear\");\n\ 
                setTimeout(function() {\n\ 
                        reconnect.style.display = \"none\";\n\ 
                    },\n\ 
                    reconnect_delay);\n\ 
            } else {\n\ 
                setTimeout(function() {\n\ 
                    reconnect.style.display = \"inline-block\";\n\ 
                    reconnect.classList.remove(\"reconnect-disappear\");\n\ 
                    reconnect.classList.add(\"reconnect-appear\");\n\ 
                }, reconnect_delay);\n\ 
            }\n\ 
        }\n\ 
\n\ 
        var isOnline = 1;\n\ 
        var username = \"-\";\n\ 
        var nodeCoords;\n\ 
\n\ 
        /* Send GPS locations + obtain name */\n\ 
        window.onload = function() {\n\ 
            console.log(\"start\");\n\ 
            setTimeout(function() {\n\ 
                if (navigator.geolocation) {\n\ 
                    navigator.geolocation.getCurrentPosition(position => {\n\ 
                        nodeCoords = position.coords;\n\ 
                        websocket.send(\"2|\" + String(nodeCoords.longitude) +\n\ 
                            \",\" + String(nodeCoords.latitude));\n\ 
                    });\n\ 
                } else {\n\ 
                    document.alert(\"Didn't obtain GPS location. Node may not work\");\n\ 
                }\n\ 
\n\ 
                username = prompt(\"Your username: \", \"username\");\n\ 
            }, 1800);\n\ 
\n\ 
\n\ 
            let reconnect = document.getElementById(\"reconnect\");\n\ 
            reconnect.style.display = \"none\";\n\ 
            /*\n\ 
            reconnect.classList.remove(\"reconnect-appear\");\n\ 
            setTimeout(function() {\n\ 
                reconnect.style.display = \"inline-block\";\n\ 
                reconnect.classList.add(\"reconnect-appear\");\n\ 
            }, reconnect_delay); */\n\ 
\n\ 
            reconnect.addEventListener(\"click\", function() {\n\ 
                reconnect.classList.remove('rotation-class');\n\ 
                setTimeout(function() {\n\ 
                    reconnect.classList.add('rotation-class')\n\ 
                }, 5);\n\ 
            }, false);\n\ 
\n\ 
\n\ 
            let send_button = document.getElementById(\"send-message\");\n\ 
            send_button.addEventListener(\"click\", function() {\n\ 
                send_button.classList.remove('send-class');\n\ 
                setTimeout(function() {\n\ 
                    send_button.classList.add('send-class');\n\ 
                }, 5);\n\ 
            }, false);\n\ 
\n\ 
            initWebSocket();\n\ 
            console.log(\"Web socket started!\");\n\ 
        };\n\ 
\n\ 
        document.getElementById(\"send-message\").onclick = () => sendMessage();\n\ 
\n\ 
        document.addEventListener('keydown', (event) => {\n\ 
            if (event.which === 13) {\n\ 
                document.getElementById(\"send-message\").classList.remove('send-class');\n\ 
                setTimeout(function() {\n\ 
                    document.getElementById(\"reconnect\").classList.add('send-class');\n\ 
                }, 5);\n\ 
                sendMessage();\n\ 
                return false;\n\ 
            }\n\ 
        });\n\ 
    </script>\n\ 
</body>\n\ 
";

#endif