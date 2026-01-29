# 💬 Dialogue System Plus

Built using Unreal Engine 5 and C++, this system allows developers to design complex dialogues using a visual, node-based workflow.

## 📖 Overview

Traditional dialogue systems often rely on CSV, JSON, or even Excel files, which can become problem for writers. This system eliminates those challenges by leveraging Custom K2Nodes within the Unreal Blueprint Graph, allowing for a fully visual authoring experience.

Furthermore, the dialogue is dynamic; branching paths and responses adapt in real-time based on the NPC's mood, your previous choices, triggered events in game and how you treat them. Detailed workflow and system mechanics are outlined below.

## ✨Features

### 🧩 1. Custom Graph Editor

Actually it's not real custom graph. Instead, I used a UObject-based Blueprint as my own custom graph.

#### 1.1 Custom K2Nodes

These custom K2Nodes are the actual pieces that make visual dialogue authoring possible. The system is built around three core node types: NPC Dialogue Node, Player Dialogue Node and Choice Node.

![customnodes](https://github.com/user-attachments/assets/dc005524-f115-4695-bb61-bc5267cbc3d4)


- **NPC Dialogue Node**: It allows us to write the dialogue lines to be spoken by the NPC.
- **Player Dialogue Node**: It allows us to write the dialogue lines to be spoken by the Player.
- **Choice Node**: It allows us to make choices.

#### 1.2 Auto-Compilation



https://github.com/user-attachments/assets/47f5fd62-c5c0-4088-8c52-50578a58bec2



Thanks to our DialogueWriter class, we bake the dialogues created with custom K2Nodes in BP_DialogueWriter to avoid optimization issues during gameplay. 
The logic is simple: when you finish writing and hit Compile button in BP_DialogueWriter, the system automatically exports all dialogue data from the graph into a DataTable. 
This ensures that at runtime, we don't waste resources searching through the Blueprint Graph; instead, we fetch the data directly from the DataTable.

Furthermore, NPC dialogues, player dialogues, and choices are stored in separate DataTables. This segregation prevents performance bottlenecks that might occur from keeping all dialogue data in a single, massive table.

### 💾 2. Dynamic NPC Memory System

Interactions with NPC are not static. These interactions are dynamically updated based on the variables listed below:

- Previous Choices and Dialogues
- Current NPC Mood
- Triggered Events on the Game

This architecture ensures that dialogues are context-aware, adapting in real-time to game events, past interactions, and the NPC’s emotional state.

### 🧠 3. Subsystems

This system utilizes three core subsystems to manage its logic: Dialogue Subsystem, Event Manager Subsystem, and Localization Subsystem.

#### 3.1 Dialogue Subsystem

This subsystem is the central hub for managing all dialogue operations, including:

- **Dialogue Scoring**: Logic for evaluating and selecting the most scored dialogue (detailed in the system design section).
- **Dialogue Display**: Handling the displaying dialogue.
- **Input Management During Dialogue**: 
- **"Do Not Disturb" Logic**: Allowing NPCs to give temporary, contextual responses when they are busy or unavailable.
- **Player Positioning**: Automatically adjusting the player's position to ensure a clear line of sight with the NPC, preventing obstacles from blocking the interaction.
- **NPC Orientation**: Dynamically rotating the NPC to face the player if approached from behind, ensuring eye contact.
- **Skip Functionality**: Managing the "Skip Dialogue" feature for players.
- 
  ![Ekran görüntüsü_29-1-2026_20713_](https://github.com/user-attachments/assets/d8e07496-db68-4303-81e3-243574803350)


  
#### 3.2 Event Manager Subsystem

This subsystem allows us to trigger game events at any point during gameplay and maintains persistent memory of triggered game events.

![event](https://github.com/user-attachments/assets/1adf119c-0304-4257-a1f7-1ac3f181da51)



#### 3.3 Localization Subsystem

While this subsystem isn't a core requirement for the dialogue system (as localization can be handled in many ways) i wanted to include it as a built-in feature. 
It manages language switching based on the settings selected in the main menu and allows for changing the default game language. 
Furthermore, once a culture is localized in the Localization Dashboard, it can be easily integrated through this subsystem.

All you need to do is add the culture code and the native name of the language to the arrays shown in the image, in the specified order.

![localization](https://github.com/user-attachments/assets/381c739c-d917-4544-a77d-a80ba39c3754)


### 🗣 4. Interaction System

Naturally, to speak with an NPC, we first need to interact with them. This system provides that functionality through a interfaces. Additionally, the system includes interaction icons to guide the player.



https://github.com/user-attachments/assets/15c0a24c-6695-41cc-8490-cfb6ac62345f


### 🍏 5. Instance Mesh Manager

This feature automates the random generation of instanced meshes within collision bounds, saving us from the time and performance optimization over manual arrangement.

This feature isn't essential to the dialogue system itself, but since the NPC's in my demo are vendors selling items like apples and lemons, I developed it.




https://github.com/user-attachments/assets/8c97e2b2-d37f-4ed9-adb3-27fc86ca02d1


### 🕵 6. Real Time Name Expose

Imagine you are developing a game where the speaker's name appears in the subtitles, similar to Cyberpunk 2077. You might want to customize this name based on whether the player has actually met or learned the NPC's identity.

In the demo, for example, a character is initially labeled as "Apple Seller." However, after interacting and having him reveal his name, the subtitle dynamically updates to display his real name. 
Additionally, you can apply this same logic to the player's name as well.



To implement this, all you need to do is go to the Custom Dialogue Node where your NPC's name is exposed, and select the corresponding event from the "Events to Trigger" section.



https://github.com/user-attachments/assets/0af0f24f-87d0-43fd-9ad2-697ad6f65763




## 🛠️ System Design

### 1. General System Design

The image below illustrates the general system design.

<img width="5312" height="1200" alt="General Architecture" src="https://github.com/user-attachments/assets/36592f83-2cc5-4f5d-99b0-0b5be045fed5" />


### 2. Dialogue Subsystem Design

The image below illustrates the Dialogue Subsystem design.

<img width="7410" height="1773" alt="Subsystem" src="https://github.com/user-attachments/assets/06963401-d8f1-4613-bff9-1637c49e2a3c" />

### 3. Dialogue Writer System Design

The image below illustrates the Dialogue Writer design.


<img width="6280" height="1560" alt="Dialogue Writer Archhitecture" src="https://github.com/user-attachments/assets/603267a8-3218-41ce-9283-18101f30d617" />

## 🔮 Future Roadmap


This project is currently in the Prototype phase. Planned improvements for the next update includes:

- **Hardcoded Elemenets:**  There are many hardcoded elements in this project. For instance, the DataTables, dialogue collisions, the number of choices we can make on the Choice Node, Name Exposing, NPCs and their names are all hardcoded. This will be refactored to allow for easy implementation into other projects.
- **Requirement Check:** Like many other advanced dialogue systems, I want to bring requirement checks to any dialogue we want.
- **Bark System** 
- **UI:** The UI looks very simple right now. I know the dialogue system and the UI are not directly related, but I want to fix this in the future.
- **Releasing this project as a plugin**
- **The overlapping issue between the meshes of the Instanced Mesh Manager**

## ✍️ Author

**Kerem Kaan Tekelek**

- **Mail:** keremtekelek@gmail.com
- **Linkedin:** https://www.linkedin.com/in/kerem-kaan-tekelek/


