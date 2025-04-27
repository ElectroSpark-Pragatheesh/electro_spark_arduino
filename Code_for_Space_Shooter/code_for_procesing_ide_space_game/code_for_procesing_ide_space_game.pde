import processing.serial.*;

Serial myPort; // Serial connection

// Spaceship
int spaceshipX;
int spaceshipY;

// Bullet (Player)
int bulletX, bulletY;
boolean bulletFired = false;

// Enemies
int[][] enemies; // x, y

// Stars
float[] starX = new float[100];
float[] starY = new float[100];
float[] starSpeed = new float[100];

// Game Status
boolean gameOver = false;

// Score
int score = 0;
int highScore = 0;

void setup() {
  size(600, 800);
  myPort = new Serial(this, "COM9", 9600); // Change COM port if needed
  myPort.bufferUntil('\n');
  
  spaceshipX = width/2;
  spaceshipY = height - 100;
  
  enemies = new int[5][2];
  
  for (int i = 0; i < enemies.length; i++) {
    enemies[i][0] = int(random(50, width-50));
    enemies[i][1] = int(random(-500, -50));
  }
  
  // Create random stars
  for (int i = 0; i < starX.length; i++) {
    starX[i] = random(width);
    starY[i] = random(height);
    starSpeed[i] = random(1, 3);
  }
  
  textAlign(CENTER);
  textSize(32);
}

void draw() {
  background(0);
  drawStars();
  
  if (!gameOver) {
    drawSpaceship();
    moveBullet();
    drawEnemies();
    checkBulletHit();
    checkCollision();
    drawScore();
  } else {
    fill(255, 0, 0);
    textAlign(CENTER);
    textSize(70);
    text("GAME OVER", width/2, height/2 - 50);
    fill(255);
    textSize(32);
    text("Score: " + score, width/2, height/2 + 10);
    text("High Score: " + highScore, width/2, height/2 + 50);
    text("Press Button to Restart", width/2, height/2 + 100);
  }
}

void serialEvent(Serial myPort) {
  String data = myPort.readStringUntil('\n');
  if (data != null) {
    data = trim(data);
    String[] parts = split(data, ',');
    if (parts.length == 3) {
      int x = int(parts[0]);
      int y = int(parts[1]);
      int button = int(parts[2]);
      
      if (!gameOver) {
        // Correct joystick directions ✅
        if (x > 600) {
          spaceshipX -= 6; // Move left
        } else if (x < 400) {
          spaceshipX += 6; // Move right
        }
        
        if (y > 600) {
          spaceshipY += 6; // Move DOWN ✅
        } else if (y < 400) {
          spaceshipY -= 6; // Move UP ✅
        }
        
        spaceshipX = constrain(spaceshipX, 20, width-20);
        spaceshipY = constrain(spaceshipY, 20, height-20);
        
        if (button == 0 && !bulletFired) {
          bulletX = spaceshipX;
          bulletY = spaceshipY;
          bulletFired = true;
        }
      } else {
        if (button == 0) {
          restartGame();
        }
      }
    }
  }
}

void drawSpaceship() {
  fill(0, 255, 255);
  noStroke();
  triangle(spaceshipX, spaceshipY-20, spaceshipX-15, spaceshipY+20, spaceshipX+15, spaceshipY+20);
}

void moveBullet() {
  if (bulletFired) {
    fill(255, 255, 0);
    ellipse(bulletX, bulletY, 8, 8);
    bulletY -= 12;
    
    if (bulletY < 0) {
      bulletFired = false;
    }
  }
}

void drawEnemies() {
  fill(255, 100, 100);
  for (int i = 0; i < enemies.length; i++) {
    ellipse(enemies[i][0], enemies[i][1], 30, 30);
    enemies[i][1] += 2; // Slow enemies
    
    if (enemies[i][1] > height) {
      enemies[i][0] = int(random(50, width-50));
      enemies[i][1] = int(random(-500, -50));
    }
  }
}

void checkBulletHit() {
  for (int i = 0; i < enemies.length; i++) {
    if (bulletFired && dist(bulletX, bulletY, enemies[i][0], enemies[i][1]) < 20) {
      enemies[i][0] = int(random(50, width-50));
      enemies[i][1] = int(random(-500, -50));
      bulletFired = false;
      score += 10;
      if (score > highScore) {
        highScore = score;
      }
    }
  }
}

void checkCollision() {
  for (int i = 0; i < enemies.length; i++) {
    if (dist(spaceshipX, spaceshipY, enemies[i][0], enemies[i][1]) < 25) {
      gameOver = true;
    }
  }
}

void restartGame() {
  gameOver = false;
  score = 0;
  spaceshipX = width/2;
  spaceshipY = height - 100;
  
  for (int i = 0; i < enemies.length; i++) {
    enemies[i][0] = int(random(50, width-50));
    enemies[i][1] = int(random(-500, -50));
  }
}

void drawScore() {
  fill(255);
  textAlign(LEFT);
  text("Score: " + score, 20, 40);
  textAlign(RIGHT);
  text("High Score: " + highScore, width-20, 40);
}

void drawStars() {
  fill(255);
  for (int i = 0; i < starX.length; i++) {
    ellipse(starX[i], starY[i], 2, 2);
    starY[i] += starSpeed[i];
    
    if (starY[i] > height) {
      starX[i] = random(width);
      starY[i] = 0;
      starSpeed[i] = random(1, 3);
    }
  }
}
