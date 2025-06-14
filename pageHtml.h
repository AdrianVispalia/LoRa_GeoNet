#ifndef _PAGE_HTML_H
#define _PAGE_HTML_H

const char index_html[] PROGMEM =  R"rawliteral(
<!DOCTYPE HTML>
<html>
<head>
    <link rel="icon" href="../Telegram_Logo.svg">
    <title>LoRa GeoNet</title>
    <meta name="viewport" content="width=device-width, initial-scale=1, maximum-scale=1">
    <style>
         :root {
            --placeholder-color: #d4d3d3a3;
        }
        
        body {
            margin: 0;
        }
        
        div {
            width: auto;
            word-break: break-word;
            text-align: left;
        }
        
        @-webkit-keyframes animation-online {
            0% {
                background-position: 0% 0%
            }
            100% {
                background-position: 100% 100%
            }
        }
        
        @-moz-keyframes animation-online {
            0% {
                background-position: 0% 0%
            }
            100% {
                background-position: 100% 100%
            }
        }
        
        @keyframes animation-online {
            0% {
                background-position: 0% 0%
            }
            100% {
                background-position: 100% 100%
            }
        }
        
        @-webkit-keyframes animation-offline {
            0% {
                background-position: 100% 100%
            }
            100% {
                background-position: 0% 0%
            }
        }
        
        @-moz-keyframes animation-offline {
            0% {
                background-position: 100% 100%
            }
            100% {
                background-position: 0% 0%
            }
        }
        
        @keyframes animation-offline {
            0% {
                background-position: 100% 100%
            }
            100% {
                background-position: 0% 0%
            }
        }
        
        .online {
            -webkit-animation: animation-online 2s ease;
            -moz-animation: animation-online 2s ease;
            animation: animation-online 2s ease;
            animation-fill-mode: forwards;
        }
        
        .offline {
            -webkit-animation: animation-offline 2s ease;
            -moz-animation: animation-offline 2s ease;
            animation: animation-offline 2s ease;
            animation-fill-mode: forwards;
        }
        
        #main-frame {
            top: 0;
            left: 0;
            height: 100vh;
            background: linear-gradient(122.5deg, rgba(224, 2, 2, 1), rgba(255, 141, 0, 1), rgba(254, 255, 0, 1), rgba(29, 197, 217, 1), rgba(35, 61, 190, 1), rgba(157, 4, 167, 1));
            background-size: 300% 300%;
        }
        
        .chat {
            position: relative;
            overflow: hidden;
            margin-right: auto;
            margin-left: auto;
            top: 10%;
            width: 50%;
            height: 80%;
            min-width: 340px;
            background-color: rgba(0, 0, 0, 0.5);
            color: white;
            border-radius: 20px;
            -webkit-animation: bounce-animation .6s ease-in-out;
            -moz-animation: bounce-animation .6s ease-in-out;
            animation: bounce-animation .6s ease-in-out;
        }
        
        @media(max-width: 480px) {
            .chat {
                top: 2%;
                width: 90%;
                height: 86%;
            }
        }
        
        .chat-title {
            /* height: 6.5%; */
            padding: 0.8vh;
            padding-left: 2.2vh;
            background: rgba(0, 0, 0, 0.2);
        }
        
        .chat-title h1 {
            margin: 0;
            text-align: center;
            font-family: Georgia, serif;
            color: #ffffffc0;
        }
        
        .target-container {
            padding: 0.8vh;
            padding-left: 2.2vh;
            background: rgba(0, 0, 0, 0.15);
            display: flex;
            padding: 1.8%;
            padding-left: 3%;
            padding-right: 3%;
            align-items: center;
            place-content: space-between;
        }
        
        .target-container h2 {
            margin: 0;
            text-align: left;
            font-family: Georgia, serif;
            color: #ffffffc0;
            display: inline;
        }
        
        .target-form {
            display: contents;
        }
        
        .target-container label {
            margin: 0;
            font-family: Georgia, serif;
            color: #ffffffc0;
            padding: 0.5%;
        }
        
        .target-container input {
            background: rgba(255, 255, 255, 0.427);
            border-radius: 4px;
            width: 12%;
        }
        
        @media(max-width: 730px) {
            .target-container input {
                width: 10%;
            }
        }
        
         ::-webkit-scrollbar {
            width: 7px;
        }
        
         ::-webkit-scrollbar-track {
            background: rgba(0, 0, 0, 0);
        }
        
         ::-webkit-scrollbar-thumb {
            background: rgba(0, 0, 0, 0.28);
            border-radius: 75vh;
        }
        
         ::-webkit-scrollbar-thumb:hover {
            background: rgba(0, 0, 0, 0.44);
            width: 8px;
        }
        
        .messages {
            /* height: 60vh; */
            height: 83%;
            overflow: auto;
            margin: 1.5%;
            margin-top: 0%;
            margin-bottom: 0%;
            padding-left: 2%;
            padding-right: 2%;
        }
        
        @media(max-width: 1100px) {
            .messages {
                height: 81.5%;
            }
        }
        
        .messages-content {
            width: auto;
            height: auto;
        }
        
        .messages .message .avatar img {
            width: 100%;
            height: auto;
        }
        
        .message {
            width: fit-content;
            width: -moz-fit-content;
            padding: 1.5%;
            padding-top: 0.55%;
            padding-bottom: 0.55%;
            margin-top: 1.6%;
            display: block;
            color: #fff;
            text-align: right;
            background: rgba(0, 0, 0, 0.3);
            border-radius: 10px 10px 10px 0;
            color: rgba(255, 255, 255, 0.5);
            max-width: 72%;
        }
        
        .new-message {
            -webkit-animation: bounce-animation .4s ease-in-out;
            -moz-animation: bounce-animation .4s ease-in-out;
            animation: bounce-animation .4s ease-in-out;
        }
        
        @media(max-width: 1100px) {
            .message {
                padding: 2.5%;
                padding-top: 1.7%;
                padding-bottom: 1.7%;
                margin-top: 2.6%;
                max-width: 82%;
            }
        }
        
        .message-personal {
            margin-left: auto;
            margin-right: 0.3%;
            border-radius: 10px 10px 0 10px;
            color: white;
            background: linear-gradient(122.5deg, #ff0000, rgba(255, 128, 0, 1), #319ac9, #364eb6);
            background-size: 300% 300%;
        }
        
        .message-box {
            position: absolute;
            bottom: 0;
            width: -webkit-fill-available;
            padding-bottom: 2.5%;
            padding-left: 4%;
            padding-right: 4%;
            padding-top: 3%;
            background: linear-gradient(122.5deg, rgb(98 38 0), rgb(101 51 0), rgb(102 72 0), rgb(20 22 74), rgb(32 16 72), rgb(47 8 70));
            background-size: 300% 300%;
        }
        
        .message-box .message-input {
            height: 1.2em;
        }
        
        textarea {
            border: none;
            overflow: auto;
            outline: none;
            -webkit-box-shadow: none;
            -moz-box-shadow: none;
            box-shadow: none;
            resize: none;
        }
        
        textarea::placeholder {
            color: var(--placeholder-color);
        }
        
        textarea:-ms-input-placeholder {
            color: var(--placeholder-color);
        }
        
        textarea::-ms-input-placeholder {
            color: var(--placeholder-color);
        }
        
        .message-input {
            color: #ffffff;
            padding: 1%;
            padding-left: 2%;
            border-radius: 0.7vw;
            width: 78%;
            background: linear-gradient(122.5deg, #bc2b2b45, #85701c3d, #233fbe45, #651eb23d);
            background-size: 300% 300%;
        }
        
        @keyframes online-input-animation {
            0% {
                width: 78%;
                background-position: 0% 0%;
            }
            100% {
                width: 85%;
                background-position: 100% 100%;
            }
        }
        
        @keyframes offline-input-animation {
            0% {
                width: 85%;
                background-position: 100% 100%;
            }
            100% {
                width: 78%;
                background-position: 0% 0%;
            }
        }
        
        .online.message-input {
            -webkit-animation: online-input-animation 2s ease;
            -moz-animation: online-input-animation 2s ease;
            animation: online-input-animation 2s ease;
            animation-fill-mode: forwards;
            animation-delay: 400ms;
        }
        
        .offline.message-input {
            -webkit-animation: offline-input-animation 2s ease;
            -moz-animation: offline-input-animation 2s ease;
            animation: offline-input-animation 2s ease;
            animation-fill-mode: forwards;
        }
        
        .message-box .message-submit {
            border-radius: 55%;
            background: transparent;
            cursor: pointer;
            padding: 0px 0px;
            /* width: 5%; */
            float: right;
        }
        
        .online.message-submit:hover {
            background: #233dbe;
            box-shadow: 0px 0px 2px 4px rgba(35, 61, 190, 0.8);
        }
        
        .offline.message-submit:hover {
            background: #b2491e;
            box-shadow: 0px 0px 2px 4px rgb(202 44 0 / 83%);
        }
        
        @keyframes appear {
            0% {
                color: rgba(255, 255, 255, 0);
            }
            100% {
                color: rgba(255, 255, 255, 1);
            }
        }
        
        @keyframes disappear {
            0% {
                color: rgba(255, 255, 255, 1);
            }
            100% {
                color: rgba(255, 255, 255, 0);
            }
        }
        
        .reconnect-appear {
            animation: appear 300ms ease-in-out;
            -webkit-transition: appear 300ms ease-in-out;
            -ms-transition: appear 300ms ease-in-out;
            animation-fill-mode: forwards;
        }
        
        .reconnect-disappear {
            animation: disappear 300ms ease-in-out;
            -webkit-transition: disappear 300ms ease-in-out;
            -ms-transition: disappear 300ms ease-in-out;
            animation-fill-mode: forwards;
        }
        
        #reconnect {
            border-radius: 35%;
            margin-right: 2.2%;
            display: none;
        }
        
        .rotation-class {
            animation: rotate 600ms ease-in-out;
            -webkit-transition: rotate 600ms ease-in-out;
            -ms-transition: rotate 600ms ease-in-out;
        }
        
        @keyframes rotate {
            0% {
                transform: rotate(0);
            }
            100% {
                transform: rotate(360deg);
            }
        }
        
        @keyframes bounce-animation {
            0% {
                transform: scale(0.1);
                transform: translateY(0.1, 0.2);
            }
            70% {
                transform: scale(1.2);
                transform: translateY(1, 1);
            }
            100% {
                transform: scale(1);
                transform: translateY(1, 1);
            }
        }
        
        .send-class {
            animation: send-animation 1s ease-out;
        }
        
        @keyframes send-animation {
            0% {
                transform: translateX(0%);
            }
            15% {
                transform: translateX(-15%);
            }
            35% {
                transform: translateX(25%);
            }
            100% {
                transform: translateX(0%);
            }
        }
    </style>
</head>

<body>
    <div class="bg online" id="main-frame">
        <div class="chat">
            <div class="chat-title">
                <h1>LoRa GeoNet</h1>
            </div>
            <div class="target-container">
                <h2>To:</h2>
                <form class="target-form">
                    <label for="lat">Latitude:</label>
                    <input type="number" id="latitude" name="lat" max="90.0" min="-90.0" value="0.0">
                    <label for="lon">Longitude:</label>
                    <input type="number" id="longitude" name="lon" max="180.0" min="-180.0" value="0.0">
                </form>
            </div>
            <div class="messages">
                <div class="messages-content" id="messages-container"></div>
            </div>
            <div class="message-box online" id="message-textarea-container">
                <textarea type="text" class="message-input online" id="message-textarea" placeholder="Message"></textarea>

                <svg width="24" height="24" class="message-submit online" id="send-message">
           <path fill="currentColor" d="M 1.101 21.757 L 23.8 12.028 L 1.101 2.3 l 2.899 7.7 l 10.967 1.606 l -10.878 2.404 l -2.932 7.764 z"></path>
         </svg>
                <svg width="26" height="24" class="message-submit offline" id="reconnect">
           <path transform="scale(1, -1) translate(0, -24)" fill="currentColor"
           d="M11.14.16c-2.9.4-5.56 2.22-7.04 4.8-.74 1.28-1.18 2.76-1.3 4.24l-.2 6.72h-2.8l5.38 7.52 4.02-7.52h-2.84q-.8-8.8 4.8-15.8z
           M14.14 23.36c2.9-.4 5.56-2.22 7.04-4.8.74-1.28 1.18-2.76 1.3-4.24l.2-6.72h2.8l-5.38-7.52-4.02 7.52h2.84q.8 8.8-4.8 15.8z"></path>
         </svg>
            </div>
        </div>
    </div>
    <script>
        /* WebSocket Section */
        var gateway = 'ws://' + window.location.hostname + '/ws';
        var websocket;

        function initWebSocket() {
            console.log('Trying to open a WebSocket connection...');
            websocket = new WebSocket(gateway);
            websocket.onopen = onOpen;
            websocket.onclose = onClose;
            websocket.onmessage = onMessage;
            if (isOnline == false) changeStatus(false);
        }

        function onOpen(event) {
            changeStatus(true);
            console.log('Connection opened');
        }

        function onClose(event) {
            changeStatus(false);
            console.log('Connection closed');
            setTimeout(initWebSocket, 2000); // try to reconnect */
        }

        function onMessage(event) {
            console.log("onMessage");
            console.log(event);

            if (event.data.length < 1) return;

            switch (event.data[0]) {
                case '1':
                    addMsgToChat(event);
                    break;
                case '2':
                    window.alert(event.data.split("|")[1]);
                    break;
                default:
                    console.log("Error onMessage unkown type:");
                    console.log(event);
            }
        }

        /* Msg GUI & logic section */
        function addMsgToChat(event) {
            let messages_content = document.getElementById("messages-container");
            const node = document.createElement("div");
            node.classList.add("message");
            if (event.data.split("|")[2] == username) {
                node.innerHTML = event.data.split("|")[3];
                node.classList.add("message-personal", "online");
                document.getElementById("message-textarea").value = "";
            } else {
                node.innerHTML = event.data.split("|")[2] + ': ' + event.data.split("|")[3];
            }
            messages_content.appendChild(node);
            messages_content.scrollIntoView(false);
        }

        var reconnect_delay = window.innerWidth > 420 ? 400 : 1200;

        function checkMsg(msg) {
            if (msg.trim() == '') {
                return false;
            }

            if (msg.length > 30 || msg.includes("|")) {
                alert(msg.length > 30 ? "Error! Too many characters" : "Error! Msg shouldn't have '|' character");
                return false;
            }

            return true;
        }

        function sendMessage() {
            let message = document.getElementById("message-textarea").value;

            if (checkMsg(message) == false) {
                return;
            }

            websocket.send("1|" +
                String(document.getElementById("longitude").value) + "," +
                String(document.getElementById("latitude").value) + "|" +
                String(username) + "|" +
                String(message));
            document.getElementById("message-textarea").value = "";
            console.log("sent this through websocket: " + message);

            /*
            let last = document.getElementById("messages-container").lastElementChild;
            last.classList.add('new-message');
            setTimeout(
                function() {
                    last.classList.remove('new-message')
                    last.classList.add(isOnline ? "online" : "offline");
                    last.classList.remove(isOnline ? "offline" : "online");
                },
                1000);
            */
        }

        /* Offline functinality */
        function changeStatus(isOnline) {
            reconnect_delay = window.innerWidth > 420 ? 400 : 1200;
            console.log("changeStatus: " + isOnline);

            let elements = [document.getElementById("main-frame"),
                document.getElementById("message-textarea-container"),
                document.getElementById("message-textarea"),
                document.getElementById("send-message")
            ];
            let messages_personal = document.getElementsByClassName("message-personal");
            let reconnect = document.getElementById("reconnect");

            let add_class = isOnline ? "online" : "offline";
            let remove_class = isOnline ? "offline" : "online";

            for (let element of elements) {
                element.classList.remove(remove_class);
                element.classList.add(add_class);
            }

            for (let msg of messages_personal) {
                msg.classList.remove(remove_class);
                msg.classList.add(add_class);
            }

            reconnect.classList.remove("rotation-class");
            if (isOnline == 1) {
                reconnect.classList.remove("reconnect-appear");
                reconnect.classList.add("reconnect-disappear");
                setTimeout(function() {
                        reconnect.style.display = "none";
                    },
                    reconnect_delay);
            } else {
                setTimeout(function() {
                    reconnect.style.display = "inline-block";
                    reconnect.classList.remove("reconnect-disappear");
                    reconnect.classList.add("reconnect-appear");
                }, reconnect_delay);
            }
        }

        var isOnline = 1;
        var username = "-";
        var nodeCoords;

        /* Send GPS locations + obtain name */
        window.onload = function() {
            console.log("start");
            setTimeout(function() {
                if (navigator.geolocation) {
                    navigator.geolocation.getCurrentPosition(position => {
                        nodeCoords = position.coords;
                        websocket.send("2|" + String(nodeCoords.longitude) +
                            "," + String(nodeCoords.latitude));
                    });
                } else {
                    document.alert("Didn't obtain GPS location. Node may not work");
                }

                username = prompt("Your username: ", "username");
            }, 1800);


            let reconnect = document.getElementById("reconnect");
            reconnect.style.display = "none";
            /*
            reconnect.classList.remove("reconnect-appear");
            setTimeout(function() {
                reconnect.style.display = "inline-block";
                reconnect.classList.add("reconnect-appear");
            }, reconnect_delay); */

            reconnect.addEventListener("click", function() {
                reconnect.classList.remove('rotation-class');
                setTimeout(function() {
                    reconnect.classList.add('rotation-class')
                }, 5);
            }, false);


            let send_button = document.getElementById("send-message");
            send_button.addEventListener("click", function() {
                send_button.classList.remove('send-class');
                setTimeout(function() {
                    send_button.classList.add('send-class');
                }, 5);
            }, false);

            initWebSocket();
            console.log("Web socket started!");
        };

        document.getElementById("send-message").onclick = () => sendMessage();

        document.addEventListener('keydown', (event) => {
            if (event.which === 13) {
                document.getElementById("send-message").classList.remove('send-class');
                setTimeout(function() {
                    document.getElementById("reconnect").classList.add('send-class');
                }, 5);
                sendMessage();
                return false;
            }
        });
    </script>
</body>
</html>
)rawliteral";

#endif
