# Sokoban - 10 Nivele Progresive în Stil Labirint

## 📊 Prezentare Generală

Am creat 10 hărți Sokoban cu dificultate progresivă, în stil labirint. Fiecare nivel este mai complex decât cel anterior.

---

## 🎮 Nivelurile

### **Level 1: Tutorial - Easy Start**

- **Dimensiuni**: 7x7
- **Cutii**: 1
- **Dificultate**: ⭐ Foarte Ușor
- **Descriere**: Nivel introductiv, simplă mișcare și plasare

### **Level 2: Corridor Challenge**

- **Dimensiuni**: 9x7
- **Cutii**: 2
- **Dificultate**: ⭐⭐ Ușor
- **Descriere**: Coridoare înguste, atenție la ordinea cutiilor

### **Level 3: Maze Runner**

- **Dimensiuni**: 10x8
- **Cutii**: 3
- **Dificultate**: ⭐⭐ Ușor-Mediu
- **Descriere**: Primul labirint adevărat cu multiple căi

### **Level 4: Twisted Paths**

- **Dimensiuni**: 11x9
- **Cutii**: 4
- **Dificultate**: ⭐⭐⭐ Mediu
- **Descriere**: Căi întortocheate, necesită planificare

### **Level 5: The Cross**

- **Dimensiuni**: 11x11
- **Cutii**: 5
- **Dificultate**: ⭐⭐⭐ Mediu
- **Descriere**: Pattern în formă de cruce, simetric

### **Level 6: Spiral Madness**

- **Dimensiuni**: 12x10
- **Cutii**: 6
- **Dificultate**: ⭐⭐⭐⭐ Mediu-Dificil
- **Descriere**: Spirală complexă cu camere interioare

### **Level 7: Double Trouble**

- **Dimensiuni**: 13x11
- **Cutii**: 6
- **Dificultate**: ⭐⭐⭐⭐ Dificil
- **Descriere**: Două secțiuni simetrice, coordonare precisă

### **Level 8: Labyrinth Legend**

- **Dimensiuni**: 14x12
- **Cutii**: 7
- **Dificultate**: ⭐⭐⭐⭐ Dificil
- **Descriere**: Labirint clasic extins, multe capcane

### **Level 9: Master's Challenge**

- **Dimensiuni**: 15x13
- **Cutii**: 8
- **Dificultate**: ⭐⭐⭐⭐⭐ Foarte Dificil
- **Descriere**: Pentru jucători experimentați, multe căi false

### **Level 10: Grandmaster's Gauntlet**

- **Dimensiuni**: 16x14
- **Cutii**: 10
- **Dificultate**: ⭐⭐⭐⭐⭐ Extrem
- **Descriere**: Provocarea supremă! Pattern complex simetric

---

## 🎯 Caracteristici Hărți

### Progresie Dificultate:

1. **Dimensiune**: Crește de la 7x7 la 16x14
2. **Număr cutii**: De la 1 la 10
3. **Complexitate labirint**: De la simplu la extrem de complex
4. **Capcane**: Crește numărul de zone periculoase

### Design Pattern:

- **Labirinturi cu coridoare**
- **Camere interioare**
- **Pattern-uri simetrice**
- **Căi false și capcane**
- **Zone centrale deschise**

---

## 🕹️ Controale UI

### Navigare Nivele:

- **N** - Următorul nivel (după completare sau oricând)
- **R** - Restart nivel curent
- **Arrow Keys / WASD** - Mișcare jucător
- **ESC** - Ieșire din joc

### Indicator UI:

- **Level: X/10** - Arată progresul (cyan, stânga sus)
- **Moves: X** - Numărul de mișcări (alb)
- **Status Message** - Feedback (galben)

---

## 📝 Legenda Hărții

- **0** = PATH (podea liberă - bej)
- **1** = TARGET (poziție target - cerc roz)
- **2** = WALL (zid - pietre gri)

### Elemente Vizuale:

- 🧱 **Ziduri** - Pattern de pietre gri
- 📦 **Cutii** - Portocalii cu X
- 🎯 **Targete** - Cercuri roz
- 👤 **Jucător** - Personaj albastru

---

## 🏆 Sistem de Progres

### Completare Nivel:

1. Jucătorul mută toate cutiile pe targete
2. Apare mesaj: **"Level Complete! Press N for next level"**
3. Apasă **N** pentru următorul nivel
4. Harta se reîncarcă automat cu dimensiuni și dificultate crescută

### La Nivel 10:

- După completare: **"You've completed all levels! Congratulations!"**
- Poți reîncărca orice nivel apăsând **N**

---

## 🔧 Implementare Tehnică

### Observer Pattern:

```cpp
game.checkWinCondition() → true
game.notify(LEVEL_WON)
view.onNotify(LEVEL_WON) → "Press N for next level"
view.handleInput() → KEY_N
view.loadNextLevel()
game.loadLevel(nextLevel)
game.notify(LEVEL_RELOADED)
view.onNotify(LEVEL_RELOADED) → recalculate offsets
```

### Adaptare Automată:

- Tile size se ajustează automat pentru fiecare nivel
- Offset-uri calculate pentru centrare
- Tile size clamped între 32-64 pixeli

---

## 🎨 Experiența de Joc

### Feedback Vizual:

- Cutiile pe target = portocaliu închis
- Counter de mișcări în timp real
- Indicator progres nivel

### Strategie:

- Nivelurile 1-3: Învață mecanicile de bază
- Nivelurile 4-6: Dezvoltă strategie
- Nivelurile 7-9: Planificare avansată
- Nivelul 10: Maestru Sokoban!

---

**Mult succes și distracție plăcută! 🎮🏆**
