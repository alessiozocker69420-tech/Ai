<!DOCTYPE html>
<html lang="de">
<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>🤖 Mein KI Assistent</title>
    <style>
        /* DESIGN */
        :root {
            --bg: #0b0e14;
            --container-bg: #161b22;
            --text: #e6edf3;
            --accent: #00ffcc;
            --bot-msg: #21262d;
            --user-msg: #00ffcc;
        }

        body {
            background-color: var(--bg);
            color: var(--text);
            font-family: 'Segoe UI', sans-serif;
            display: flex;
            justify-content: center;
            align-items: center;
            height: 100vh;
            margin: 0;
        }

        .chat-box {
            width: 100%;
            max-width: 500px;
            height: 80vh;
            background: var(--container-bg);
            border-radius: 20px;
            display: flex;
            flex-direction: column;
            overflow: hidden;
            box-shadow: 0 10px 30px rgba(0,0,0,0.5);
            border: 1px solid #30363d;
        }

        .chat-header {
            padding: 20px;
            background: #1f242c;
            text-align: center;
            border-bottom: 1px solid #30363d;
        }

        .chat-header h1 { margin: 0; font-size: 1.2rem; color: var(--accent); }

        #chatMessages {
            flex: 1;
            padding: 20px;
            overflow-y: auto;
            display: flex;
            flex-direction: column;
            gap: 15px;
        }

        .msg {
            max-width: 85%;
            padding: 12px 16px;
            border-radius: 15px;
            font-size: 14px;
            line-height: 1.5;
            word-wrap: break-word;
        }

        .bot { background: var(--bot-msg); align-self: flex-start; border-bottom-left-radius: 2px; }
        .user { background: var(--user-msg); color: #0b0e14; align-self: flex-end; border-bottom-right-radius: 2px; font-weight: 500; }

        .input-area {
            padding: 20px;
            display: flex;
            gap: 10px;
            background: #1f242c;
        }

        input {
            flex: 1;
            background: #0d1117;
            border: 1px solid #30363d;
            color: white;
            padding: 12px;
            border-radius: 10px;
            outline: none;
        }

        button {
            background: var(--accent);
            border: none;
            padding: 10px 15px;
            border-radius: 10px;
            cursor: pointer;
            font-weight: bold;
            transition: 0.2s;
        }

        button:hover { transform: scale(1.05); opacity: 0.9; }

        /* Animation für "KI schreibt..." */
        .typing { font-style: italic; opacity: 0.6; font-size: 12px; }
    </style>
</head>
<body>

<div class="chat-box">
    <div class="chat-header">
        <h1>🤖 KI Assistent</h1>
    </div>
    
    <div id="chatMessages">
        <div class="msg bot">Hallo! Ich bin bereit. Was möchtest du wissen? 👋</div>
    </div>
    
    <div id="typingIndicator" style="padding: 0 20px; display: none;" class="typing">KI schreibt gerade...</div>

    <div class="input-area">
        <input type="text" id="userInput" placeholder="Schreib etwas..." onkeypress="if(event.key==='Enter') sendMessage()">
        <button onclick="sendMessage()">Senden</button>
    </div>
</div>

<script>
    // WICHTIG: Setze hier deinen Key ein, um es LOKAL zu testen.
    // Wenn du es auf GitHub hochlädst, nutze einen Platzhalter!
    const API_KEY = "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";

    async function sendMessage() {
        const input = document.getElementById('userInput');
        const container = document.getElementById('chatMessages');
        const loader = document.getElementById('typingIndicator');
        const text = input.value.trim();

        if (!text) return;

        // User Nachricht
        container.innerHTML += `<div class="msg user">${text}</div>`;
        input.value = '';
        container.scrollTop = container.scrollHeight;

        // Zeige "KI schreibt..."
        loader.style.display = 'block';

        try {
            const response = await fetch("https://openai.com", {
                method: "POST",
                headers: {
                    "Content-Type": "application/json",
                    "Authorization": `Bearer ${API_KEY}`
                },
                body: JSON.stringify({
                    model: "gpt-3.5-turbo",
                    messages: [{ role: "user", content: text }]
                })
            });

            const data = await response.json();
            loader.style.display = 'none';

            if (data.choices && data.choices[0]) {
                const reply = data.choices[0].message.content;
                container.innerHTML += `<div class="msg bot">${reply}</div>`;
            } else {
                throw new Error();
            }
        } catch (error) {
            loader.style.display = 'none';
            container.innerHTML += `<div class="msg bot" style="color: #ff6b6b;">Hoppla! Da gab es ein Problem mit dem Key oder der Verbindung.</div>`;
        }
        
        container.scrollTop = container.scrollHeight;
    }
</script>

</body>
</html>
