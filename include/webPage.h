#ifndef WEB_PAGE_H
#define WEB_PAGE_H

#include <Arduino.h>

const String webpage1 = R"(<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>Test</title>

    <style>
        *, *::before, *::after {
            box-sizing: border-box;
            margin: 0;
            padding: 0;
        }

        body {
            display: flex;
            flex-direction: column;
            min-height: 100vh;
        }

        main {
            flex: 1;
        }
        
        header.top_menu {
            display: flex;
            flex-wrap: nowrap;
            flex-direction: row; /*phone: column*/
        }
        
        header > div.menu_point {
            display: flex;
            border-bottom: 2px solid black;
            border-right: 2px solid black;
            flex-grow: 1;
            height: 3rem;
            justify-content: center;
            align-items: center;
        }

        header > div.menu_point:last-child {
            border-right: none;
        }
        
        header > div.menu_point.active {
            color: white;
            background: hsl(252, 67%, 20%);
        }

        header > div.menu_point:hover,
        header > div.menu_point.active:hover {
            color: white;
            background: hsl(252, 67%, 10%);
        }

        header > div.menu_point > * {
            pointer-events: none;
            user-select: none;
        }

        section {
            display: flex;
            justify-content: center;
            align-items: center;
            flex-direction: column;
            height: 0px;
            overflow: hidden;
        }

        section.active {
            width: initial;
            height: initial;
            overflow: initial;
            padding-top: 3rem;
        }

        .slider {
            display: grid;
            margin-top: 0.75rem;
        }

        .color_choice_full {
            margin-top: 0.75rem;
        }

        .effect_choice_options_x {
            height: 0px;
            overflow: hidden;
        }

        .effect_choice_options_x.active {
            height: initial;
            overflow: initial;
        }

        .mfk {
            padding: 1.5rem 0;
            border-bottom: 2px solid black;
        }

        #effect_choice_options_1 > .option + button {
            margin-top: 2rem;
            width: 100%;
            text-align: center;
        }
        
        input.color_picker {
            width: 8rem;
            padding: 0.25rem;
        }

        input[type="number"] {
            text-align: right;
        }

        footer.send_options {
            display: flex;
            flex-wrap: nowrap;
            flex-direction: row; /*phone: column*/
        }

        footer.send_options > div.send_option {
            display: flex;
            border-top: 2px solid black;
            border-right: 2px solid black;
            flex-grow: 1;
            height: 3rem;
            justify-content: center;
            align-items: center;
        }

        footer.send_options > div.send_option:last-child {
            border-right: none;
        }

        footer.send_options > div.test_mode > * {
            margin: 0 0.5rem;
        }

        footer.send_options > div.send_option > button {
            padding: 0 0.5rem;
        }

        @media (max-width: 320px) {
            header.top_menu, footer.send_options {
                flex-direction: column;
            }

            header > div.menu_point, footer.send_options > div.send_option {
                border-right: none;
            }
        }
    </style>
</head>
<body>
    <header class="top_menu">
        <div class="menu_point" id="single_mode">
            <h3>Feste Farbe</h3>
        </div>
        <div class="menu_point" id="effect_mode">
            <h3>Muster</h3>
        </div>
        <div class="menu_point" id="game_mode">
            <h3>Spieler-Modus</h3>
        </div>
    </header>
    <main>
        <section class="single_mode" id="single_mode_section">
            <div class="section_title">
                <h1>Feste Farbe</h1>
            </div>
            <div class="color_choice_all" id="single_mode_cca">
                <div class="color_choice">
                    <div class="color_choice_slider">
                        <div class="slider slider_r">
                            <label for="color_red">Rot:</label>
                            <input type="range" id="color_red" min="0" max="255" value="255" class="single_color_slider">
                        </div>
                        <div class="slider slider_g">
                            <label for="color_green">Grün:</label>
                            <input type="range" id="color_green" min="0" max="255" value="0" class="single_color_slider">
                        </div>
                        <div class="slider slider_b">
                            <label for="color_blue">Blau:</label>
                            <input type="range" id="color_blue" min="0" max="255" value="0" class="single_color_slider">
                        </div>
                    </div>
                </div>
                <div class="color_choice_full">
                    <label for="color_picker_feste_farbe">Farbwahl:</label>
                    <input type="color" id="color_picker_feste_farbe" value="#ff0000" class="color_picker">
                </div>
            </div>
        </section>

        <section class="effect_mode" id="effect_mode_section">
            <div class="section_title">
                <h1>Muster</h1>
            </div>
            <div class="effect_choice">
                <select name="effect_mode_choice" id="effect_mode_choice" value="0">
                    <Option value="0">Einfarb-Karusell</Option>
                    <Option value="1">Mehrfarb-Karusell</Option>
                    <Option value="2">Mehrfarb-Blinken</Option>
                    <Option value="3">Mehrfarb-Rotation</Option>
                    <Option value="4">Random-Mode</Option>
                </select>
            </div>
            <div class="effect_choice_options">
                <div class="effect_choice_options_x active" id="effect_choice_options_0">
                    <!-- Einfarb-Karusell -->
                    <h3>Einfarb-Karusell</h3>
                    <div class="options">
                        <div class="option">
                            <label for="len_0">Länge</label>
                            <input id="len_0" type="number" value="10">
                        </div>
                        <div class="option">
                            <label for="spd_0">Geschwindigkeit</label>
                            <input id="spd_0" type="number" value="5">
                            <label class="einheit">LED/s</label>
                        </div>
                        <div class="option">
                            <div class="color_choice_all" id="effect_choice_options_0_cca">
                                <div class="color_choice">
                                    <div class="color_choice_slider">
                                        <div class="slider slider_r">
                                            <label for="color_red_0">Rot:</label>
                                            <input type="range" id="color_red_0" min="0" max="255" value="255" class="single_color_slider">
                                        </div>
                                        <div class="slider slider_g">
                                            <label for="color_green_0">Grün:</label>
                                            <input type="range" id="color_green_0" min="0" max="255" value="0" class="single_color_slider">
                                        </div>
                                        <div class="slider slider_b">
                                            <label for="color_blue_0">Blau:</label>
                                            <input type="range" id="color_blue_0" min="0" max="255" value="0" class="single_color_slider">
                                        </div>
                                    </div>
                                </div>
                                <div class="color_choice_full">
                                    <label for="color_0">Farbe</label>
                                    <input type="color" id="color_0" value="#ff0000" class="color_picker">
                                </div>
                            </div>
                        </div>
                    </div>
                </div>
                <div class="effect_choice_options_x" id="effect_choice_options_1">
                    <!-- Mehrfarb-Karusell -->
                    <h3>Mehrfarb-Karusell</h3>
                    <div class="option">
                        <label for="spd_1">Geschwindigkeit</label>
                        <input id="spd_1" type="number" value="5">
                        <label class="einheit">LED/s</label>
                    </div>
                    <div class="option">
                        <div class="mfk mfk_0">
                            <div class="color_choice_all" id="effect_choice_options_1_cca_0">
                                <div class="color_choice">
                                    <div class="color_choice_slider">
                                        <div class="slider slider_r">
                                            <label for="color_red_1_0">Rot:</label>
                                            <input type="range" id="color_red_1_0" min="0" max="255" value="255" class="single_color_slider">
                                        </div>
                                        <div class="slider slider_g">
                                            <label for="color_green_1_0">Grün:</label>
                                            <input type="range" id="color_green_1_0" min="0" max="255" value="0" class="single_color_slider">
                                        </div>
                                        <div class="slider slider_b">
                                            <label for="color_blue_1_0">Blau:</label>
                                            <input type="range" id="color_blue_1_0" min="0" max="255" value="0" class="single_color_slider">
                                        </div>
                                    </div>
                                </div>
                                <div class="color_choice_full">
                                    <label for="color_1_0">Farbe</label>
                                    <input type="color" id="color_1_0" value="#ff0000" class="color_picker">
                                </div>
                            </div>
                        </div>
                        <div class="mfk mfk_1">
                            <div class="color_choice_all" id="effect_choice_options_1_cca_1">
                                <div class="color_choice">
                                    <div class="color_choice_slider">
                                        <div class="slider slider_r">
                                            <label for="color_red_1_1">Rot:</label>
                                            <input type="range" id="color_red_1_1" min="0" max="255" value="255" class="single_color_slider">
                                        </div>
                                        <div class="slider slider_g">
                                            <label for="color_green_1_1">Grün:</label>
                                            <input type="range" id="color_green_1_1" min="0" max="255" value="0" class="single_color_slider">
                                        </div>
                                        <div class="slider slider_b">
                                            <label for="color_blue_1_1">Blau:</label>
                                            <input type="range" id="color_blue_1_1" min="0" max="255" value="0" class="single_color_slider">
                                        </div>
                                    </div>
                                </div>
                                <div class="color_choice_full">
                                    <label for="color_1_1">Farbe</label>
                                    <input type="color" id="color_1_1" value="#ff0000" class="color_picker">
                                </div>
                            </div>
                        </div>
                        <div class="mfk mfk_2">
                            <div class="color_choice_all" id="effect_choice_options_1_cca_2">
                                <div class="color_choice">
                                    <div class="color_choice_slider">
                                        <div class="slider slider_r">
                                            <label for="color_red_1_2">Rot:</label>
                                            <input type="range" id="color_red_1_2" min="0" max="255" value="255" class="single_color_slider">
                                        </div>
                                        <div class="slider slider_g">
                                            <label for="color_green_1_2">Grün:</label>
                                            <input type="range" id="color_green_1_2" min="0" max="255" value="0" class="single_color_slider">
                                        </div>
                                        <div class="slider slider_b">
                                            <label for="color_blue_1_2">Blau:</label>
                                            <input type="range" id="color_blue_1_2" min="0" max="255" value="0" class="single_color_slider">
                                        </div>
                                    </div>
                                </div>
                                <div class="color_choice_full">
                                    <label for="color_1_2">Farbe</label>
                                    <input type="color" id="color_1_2" value="#ff0000" class="color_picker">
                                </div>
                            </div>
                        </div>
                    </div>
                    <button>Farbe hinzufügen</button> <!-- Farben: Min 3, "Farbe hinzufügen" Option für mehr, Max 10 Farben -->
                    <!-- Länge: Anzahl Farben/Gesamtlänge -->
                </div>
                <div class="effect_choice_options_x" id="effect_choice_options_2">
                    <h1>TO BE IMPLEMENTED</h1>
                    <!-- Mehrfarb-Blinken -->
                    <!--
                        Geschwindigkeit
                        Farben
                            Min 3, "Farbe hinzufügen" Option für mehr, Max 10 Farben
                            Länge pro Farbe (vs Gesamtlänge/Anzahl farben)
                    -->
                </div>
                <div class="effect_choice_options_x" id="effect_choice_options_3">
                    <h1>TO BE IMPLEMENTED</h1>
                    <!-- Mehrfarb-Rota -->
                    <!--
                        Alle LEDs eine Farbe, stetiger wechsel zur nächsten Farbe
                        Optionen:
                        - Geschwindigkeit (Dauer von einem Stop zum Nächsten)
                        Farben:
                        - min 3, max 10
                        - stetiger Wechsel von Farbe zu Farbe (bewegung der einzelnen Kanäle richtung Ziel)
                        - von letzter zu erster
                        - Button um weitere Farben hinzuzufügen
                    -->
                </div>
                <div class="effect_choice_options_x" id="effect_choice_options_4">
                    <h1>TO BE IMPLEMENTED</h1>
                    <!-- Random-Mode -->
                    <!--
                        Wechsel-Geschwindigkeit
                        Options Black/Whitelist (?)
                        "Warnung": Optionen die grad bei den anderen eingestellt sind werden genommen
                    -->
                </div>
                <!--
                    OPTIONAL: Beispielanimation des effekts
                    OK-Button zum senden des Effektes mit Einstellungen
                -->
            </div>
        </section>

        <section class="game_mode" id="game_mode_section">
            <div class="section_title">
                <h1>Spieler-Modus</h1>
            </div>
            <div class="game_options">
                <h1>TO BE IMPLEMENTED</h1>
                <!--
                    Optionen für Spielmodus
                    - Anzahl Spieler
                    - Position pro Spieler
                    -- Evtl mit live-auswahl-"animation"?
                    - Spieler "breite" (allgemein)
                -->
            </div>
        </section>
    </main>
    <footer class="send_options">
        <div class="send_option test_mode">
            <label for="test_mode_box" id="test_mode_label">Test Mode</label>
            <input type="checkbox" id="test_mode_box">
        </div>
        <div class="send_option">
            <button class="send_button" id="send_info_btn">Start</button>
        </div>
    </footer>

    <!--
        Inline-JS, to minimize the amount of web-related-files
    -->
    <script>
        cl = console.log;

        // SETTINGS:
        const HOST = ")";
        
const String webpage2 = R"(";
        const PORT = "80";
        const timeout = 50 /* ms */;
        
        // Global-Vars
        const test_mode_box = document.getElementById("test_mode_box");
        const MENU_SECTIONS = new Map();
        let ACTIVE_MENU_POINT = undefined;
        const COLOR_CHOICES = [];
        let ACTIVE_EFFECT_CHOICE = document.getElementById("effect_choice_options_0");
        const effect_select = document.getElementById("effect_mode_choice");
        let last_send = 0;
        let mfk_clr_amount = 3;
        const add_clr_btn = document.querySelector("#effect_choice_options_1 > .option + button");

        // Utility Functions
        Array.prototype.get = function(index) {
            if (index < 0) return this[this.length + index];
            else return this[index];
        }

        function send_infos(force = false, test_final = false) {
            const enough_time_passed = Date.now() - last_send >= timeout;
            const sending_allowed = test_mode_box.checked && (enough_time_passed || test_final);

            if (!force && !sending_allowed) return;

            let data = {};

            switch (ACTIVE_MENU_POINT.id) {
                case 'single_mode':
                    data["mode"] = "single_mode";
                    data["color"] = document.getElementById("color_picker_feste_farbe").value;
                    break;

                case 'effect_mode':
                    data["mode"] = "effect_mode";

                    switch (parseInt(ACTIVE_EFFECT_CHOICE.id.split("_").get(-1))) {
                        case 0:
                            // Einfarb-Karusell
                            data["sub_mode"] = "0";
                            data["color"] = document.getElementById("color_0").value;
                            data["length"] = document.getElementById("len_0").value;
                            data["speed"] = document.getElementById("spd_0").value;
                            break;

                        case 1:
                            // Mehrfarb-Karusell
                            data["sub_mode"] = "1";
                            data["speed"] = document.getElementById("spd_1").value;
                            data["color_count"] = `${mfk_clr_amount}`;
                            for (let i = 0; i < mfk_clr_amount; i++) {
                                data[`color_${i}`] = document.getElementById(`color_1_${i}`).value;
                            }
                            break;

                        case 2:
                            // Mehrfarb-Blinken
                            break;

                        case 3:
                            // Mehrfarb-Blinken
                            break;

                        case 4:
                            // Random
                            break;

                        default:
                            throw new Error("ACTIVE_EFFECT_CHOICE switch");
                    }
                    break;

                case 'game_mode':
                    break;

                default:
                    // rgb-mode
                    throw new Error("ACTIVE_MENU_POINT switch");
            }
            
            let full_url = `http://${HOST}:${PORT}`;
            let init_obj = {
                method: "POST",
                mode: "no-cors",
                // cache: "no-cache",
                // credentials: "same-origin",
                headers: {
                    "Content-Type": "application/json",
                },
                // referrerPolicy: "no-referrer",
                body: JSON.stringify(data),
            };
            
            fetch(full_url, init_obj);

            last_send = Date.now();
        }

        function toHex(i) {
            return (("0" + i.toString(16)).slice(-2));
        }

        function clr_all_to_picker(clr_all) {
            return `#${toHex(parseInt(clr_all.r.value, 10))}${toHex(parseInt(clr_all.g.value, 10))}${toHex(parseInt(clr_all.b.value, 10))}`
        }


        // Functions
        function add_color_choice_EventListeners(color_all) {
            const color_picker = color_all.querySelector(".color_choice_full").querySelector("input.color_picker");
            const slider_r = color_all.querySelector("div.color_choice_slider > div.slider_r > input.single_color_slider");
            const slider_g = color_all.querySelector("div.color_choice_slider > div.slider_g > input.single_color_slider");
            const slider_b = color_all.querySelector("div.color_choice_slider > div.slider_b > input.single_color_slider");

            COLOR_CHOICES.push({
                "c": color_picker,
                "r": slider_r,
                "g": slider_g,
                "b": slider_b
            });

            color_picker.addEventListener("change", e =>
            {
                const clr_all = COLOR_CHOICES.filter(o => o.c == e.target)[0];

                let color_string = e.target.value.slice(-6);

                let red = parseInt(color_string.slice(0, 2), 16);
                clr_all.r.value = red;

                let green = parseInt(color_string.slice(2, 4), 16);
                clr_all.g.value = green;
                
                let blue = parseInt(color_string.slice(4), 16);
                clr_all.b.value = blue;

                send_infos(false, true);
            });

            slider_r.addEventListener("input", e => {
                const clr_all = COLOR_CHOICES.filter(o => o.r == e.target)[0];

                clr_all.c.value = clr_all_to_picker(clr_all);
                send_infos();
            });

            slider_g.addEventListener("input", e => {
                const clr_all = COLOR_CHOICES.filter(o => o.g == e.target)[0];

                clr_all.c.value = clr_all_to_picker(clr_all);
                send_infos();
            });

            slider_b.addEventListener("input", e => {
                const clr_all = COLOR_CHOICES.filter(o => o.b == e.target)[0];

                clr_all.c.value = clr_all_to_picker(clr_all);
                send_infos();
            });

            slider_r.addEventListener("change", e => {
                // const clr_all = COLOR_CHOICES.filter(o => o.r == e.target)[0];
                
                send_infos(false, true);
            });

            slider_g.addEventListener("change", e => {
                // const clr_all = COLOR_CHOICES.filter(o => o.g == e.target)[0];

                send_infos(false, true);
            });
            
            slider_b.addEventListener("change", e => {
                // const clr_all = COLOR_CHOICES.filter(o => o.b == e.target)[0];

                send_infos(false, true);
            });
        }


        // Menu Functionality
        
        // Setup für die Menüpunkte und deren zugehörige Sections
        // ->   Klick auf Menüpunkt setzt diesen Menüpunkt und seine zugehörige Section auf "active",
        //      während die zuvor aktive Menü-Section-Combo den "active"-Status / die "active"-Klasse verliert
        for (const menu_point of document.querySelectorAll("header > div.menu_point"))
        {
            const section = document.getElementById(menu_point.id + "_section");
            MENU_SECTIONS.set(menu_point, section);

            if (!ACTIVE_MENU_POINT) {
                ACTIVE_MENU_POINT = menu_point;

                menu_point.classList.add("active");
                section.classList.add("active");
            }

            menu_point.addEventListener("click", e => {
                if (e.target == ACTIVE_MENU_POINT) return;

                if (ACTIVE_MENU_POINT)
                {
                    ACTIVE_MENU_POINT.classList.remove("active");
                    MENU_SECTIONS.get(ACTIVE_MENU_POINT).classList.remove("active");
                }

                e.target.classList.add("active");
                MENU_SECTIONS.get(e.target).classList.add("active");

                ACTIVE_MENU_POINT = e.target;
            });
        }


        // Color-Choices Functionality

        // Setup für die Color-Slider-Picker-Combo
        // ->   Wenn ein Slider angepasst wird, muss sich der Color-Picker anpassen,
        //      wenn der Color-Picker sich ändert, müssen sich die Slider anpassen
        for (const color_all of document.querySelectorAll(".color_choice_all"))
        {
            add_color_choice_EventListeners(color_all);
        }


        // Effect-Choice Functionality

        effect_select.addEventListener("change", e => {
            if (ACTIVE_EFFECT_CHOICE) {
                ACTIVE_EFFECT_CHOICE.classList.remove("active");
            }

            const id = "effect_choice_options_" + e.target.value;
            ACTIVE_EFFECT_CHOICE = document.getElementById(id);
            ACTIVE_EFFECT_CHOICE.classList.add("active");
        });

        // Mehrfarb-karusell:
        add_clr_btn.addEventListener("click", e => {
            let mfk_options_node = document.querySelector("#effect_choice_options_1 > .option");

            let node = document.createElement("div");
            node.classList.add("mfk");
            node.classList.add(`mfk_${mfk_clr_amount}`);

            node.innerHTML = `
                        <div class="color_choice_all" id="effect_choice_options_1_cca_${mfk_clr_amount}">
                            <div class="color_choice">
                                <div class="color_choice_slider">
                                    <div class="slider slider_r">
                                        <label for="color_red_1_${mfk_clr_amount}">Rot:</label>
                                        <input type="range" id="color_red_1_${mfk_clr_amount}" min="0" max="255" value="255" class="single_color_slider">
                                    </div>
                                    <div class="slider slider_g">
                                        <label for="color_green_1_${mfk_clr_amount}">Grün:</label>
                                        <input type="range" id="color_green_1_${mfk_clr_amount}" min="0" max="255" value="0" class="single_color_slider">
                                    </div>
                                    <div class="slider slider_b">
                                        <label for="color_blue_1_${mfk_clr_amount}">Blau:</label>
                                        <input type="range" id="color_blue_1_${mfk_clr_amount}" min="0" max="255" value="0" class="single_color_slider">
                                    </div>
                                </div>
                            </div>
                            <div class="color_choice_full">
                                <label for="color_1_${mfk_clr_amount}">Farbe</label>
                                <input type="color" id="color_1_${mfk_clr_amount}" value="#ff0000" class="color_picker">
                            </div>
                        </div>
`;

            mfk_options_node.appendChild(node);
            
            mfk_clr_amount++;

            let new_clr_choice = node.querySelector("div.color_choice_all");
            add_color_choice_EventListeners(new_clr_choice);
        });
    </script>
</body>
</html>)";

#endif