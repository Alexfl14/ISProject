# Sokoban Game - Design Patterns Implementation

## Proiect pentru Inginerie Software (IS)

### Design Patterns Folosite

#### 1. **Observer Pattern** 🎯

- **Subject (Subiect)**: `Game` - gestionează logica jocului
- **Observer (Observator)**: `GUI_View` - observă schimbările în joc
- **Implementare**:
  - `Game` moștenește `IGameSubject` care oferă metodele:
    - `addObserver(IGameObserver*)` - înregistrează observatori
    - `removeObserver(IGameObserver*)` - șterge observatori
    - `notify(EGameEvent)` - notifică toți observatorii
  - `GUI_View` implementează `IGameObserver` cu metoda:
    - `onNotify(EGameEvent)` - primește notificări de la Subject

#### 2. **Events Notificate**:

- `LEVEL_WON` - nivel câștigat (toate cutiile pe target)
- `LEVEL_RELOADED` - nivel reîncărcat/restart
- `PLAYER_MOVED` - jucătorul s-a mutat
- `BOX_MOVED` - o cutie a fost împinsă

### Structura Proiectului

```
SokobanCore/          # Backend (coleg)
├── Game.cpp          # Subject implementation
├── GameMap.cpp       # Map loading from JSON
├── Player.cpp        # Player logic
└── Box.cpp           # Box logic

SokobanUI/            # Frontend (implementat)
├── GUI_View.h        # Observer interface
├── GUI_View.cpp      # Observer implementation + Raylib rendering
└── main.cpp          # Game loop + Observer registration
```

### Flux Observer Pattern

1. **Inițializare**:

   ```cpp
   Game game;
   GUI_View view(&game);
   game.addObserver(&view);
   ```

2. **Notificare**:

   ```cpp
   view.handleInput()
   → game.movePlayer(direction)
   → game.notify(PLAYER_MOVED)
   → view.onNotify(PLAYER_MOVED)
   ```

3. **Cleanup**:
   ```cpp
   game.removeObserver(&view);
   ```

### Beneficiile Observer Pattern

✅ **Decuplare**: Frontend-ul (GUI_View) nu știe detalii despre backend (Game)  
✅ **Extensibilitate**: Pot fi adăugați oricâți observatori (SoundManager, Logger, etc.)  
✅ **Single Responsibility**: Game se ocupă de logică, GUI_View de afișare  
✅ **Reactive**: UI-ul se actualizează automat la schimbări

### Rulare

1. Deschide proiectul în Visual Studio
2. Build Solution (Ctrl+Shift+B)
3. Run (F5)
4. Controale:
   - Arrow Keys / WASD - mișcare
   - R - restart nivel
   - ESC - ieșire

### Notă pentru Profesor

Acest proiect demonstrează implementarea **Observer Pattern** în contextul unui joc Sokoban. Backend-ul (coleg) a implementat Subject-ul (Game), iar frontend-ul implementează Observer-ul (GUI_View) care primește notificări automate la schimbări de stare.
