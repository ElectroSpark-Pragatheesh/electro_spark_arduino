// Racing Game - FULL PRO Version for Pragatheesh 🚀🏎️

import processing.serial.*;
Serial myPort;

// Lane setup
int totalLanes = 5;
float laneWidth;
float[] laneXPositions;
int carLane = 2; // Start in middle lane

PImage playerCar;
PImage enemyCar;
float carY;

float obstacleX;
float obstacleY;
float obstacleSpeed = 5;

int score = 0;
boolean gameOver = false;

// Joystick info
int joystickX = 512;
int joystickY = 512;
int button = 1;
boolean canMove = true; // Only allow 1 move per push

void setup() {
  size(400, 600);
  
  laneWidth = width / totalLanes; // Perfectly equal lane width
  laneXPositions = new float[totalLanes];
  for (int i = 0; i < totalLanes; i++) {
    laneXPositions[i] = i * laneWidth + laneWidth/2 - 20; // Center car in lane
  }
  
  playerCar = createPlayerCarImage();
  enemyCar = createEnemyCarImage();
  
  carY = height - 100;
  
  obstacleX = randomLaneX();
  obstacleY = -40;
  
  printArray(Serial.list());
  myPort = new Serial(this, Serial.list()[0], 9600);
  myPort.bufferUntil('\n');
  
  textAlign(CENTER, CENTER);
  textSize(24);
}

void draw() {
  background(80); // Gray road

  drawLanes();
  
  if (!gameOver) {
    handleJoystick();

    // Draw Player Car
    image(playerCar, laneXPositions[carLane], carY);
    
    // Move and Draw Enemy Car
    obstacleY += obstacleSpeed;
    image(enemyCar, obstacleX, obstacleY);
    
    if (obstacleY > height) {
      obstacleY = -40;
      obstacleX = randomLaneX();
      score += 1;
    }
    
    // Collision detection
    if (laneXPositions[carLane] < obstacleX + 40 &&
        laneXPositions[carLane] + 40 > obstacleX &&
        carY < obstacleY + 60 &&
        carY + 60 > obstacleY) {
      gameOver = true;
    }
    
    fill(255);
    text("Score: " + score, width/2, 30);
    
    if (button == 0) {
      boostCar();
    }
    
  } else {
    fill(255, 0, 0);
    text("GAME OVER", width/2, height/2 - 30);
    fill(255);
    text("Press Button to Restart", width/2, height/2 + 30);
    text("Final Score: " + score, width/2, height/2 + 70);
    
    // If joystick button pressed after game over → restart
    if (button == 0) {
      restartGame();
    }
  }
}

void handleJoystick() {
  if (canMove) {
    if (joystickX > 700) { // Push right
      carLane++;
      canMove = false;
    } else if (joystickX < 300) { // Push left
      carLane--;
      canMove = false;
    }
  }
  
  if (joystickX >= 400 && joystickX <= 600) {
    canMove = true;
  }
  
  carLane = constrain(carLane, 0, totalLanes-1);
}

void serialEvent(Serial myPort) {
  String data = myPort.readStringUntil('\n');
  if (data != null) {
    data = trim(data);
    String[] values = split(data, ',');
    if (values.length == 3) {
      joystickX = int(values[0]);
      joystickY = int(values[1]);
      button = int(values[2]);
    }
  }
}

void keyPressed() {
  if (key == 'r' || key == 'R') {
    restartGame();
  }
}

void restartGame() {
  score = 0;
  carLane = 2;
  carY = height - 100;
  obstacleX = randomLaneX();
  obstacleY = -40;
  gameOver = false;
}

void drawLanes() {
  stroke(255);
  strokeWeight(2);
  for (int i = 1; i < totalLanes; i++) {
    for (int y = 0; y < height; y += 40) {
      line(i * laneWidth, y, i * laneWidth, y + 20);
    }
  }
}

float randomLaneX() {
  int lane = int(random(totalLanes));
  return laneXPositions[lane];
}

// Create player car (blue)
PImage createPlayerCarImage() {
  PImage img = createImage(40, 60, RGB);
  img.loadPixels();
  for (int y = 0; y < 60; y++) {
    for (int x = 0; x < 40; x++) {
      if (y < 20) {
        img.pixels[x + y*40] = color(0, 0, 255); // Blue roof
      } else if (y < 50) {
        img.pixels[x + y*40] = color(30, 30, 30); // Dark body
      } else {
        img.pixels[x + y*40] = color(0, 255, 0); // Green bumper
      }
    }
  }
  img.updatePixels();
  return img;
}

// Create enemy car (red)
PImage createEnemyCarImage() {
  PImage img = createImage(40, 60, RGB);
  img.loadPixels();
  for (int y = 0; y < 60; y++) {
    for (int x = 0; x < 40; x++) {
      if (y < 20) {
        img.pixels[x + y*40] = color(255, 0, 0); // Red roof
      } else if (y < 50) {
        img.pixels[x + y*40] = color(60, 0, 0); // Dark red body
      } else {
        img.pixels[x + y*40] = color(255, 255, 0); // Yellow bumper
      }
    }
  }
  img.updatePixels();
  return img;
}

void boostCar() {
  carY -= 20;
  if (carY < 0) carY = 0;
}
