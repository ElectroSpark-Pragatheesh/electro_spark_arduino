import processing.serial.*;

Serial port;

float px = 50, py = 400;    // Player position
float vx = 0, vy = 0;       // Velocity
float gravity = 0.8;
boolean onGround = false;
boolean jumpPressed = false;
boolean levelComplete = false;

void setup() {
  size(800, 600);
  port = new Serial(this, Serial.list()[0], 9600);
  port.bufferUntil('\n');
  textAlign(CENTER, CENTER);
}

void draw() {
  background(255);
  drawPlatforms();
  drawFinish();

  if (!levelComplete) {
    drawInstructions();

    // Physics
    vy += gravity;
    py += vy;
    px += vx;

    // Boundaries
    if (px < 0) px = 0;
    if (px > width) px = width;

    // Platform collision
    onGround = false;
    if (py >= 500 && px >= 100 && px <= 300) {
      py = 500;
      vy = 0;
      onGround = true;
    }
    if (py >= 400 && px >= 400 && px <= 600) {
      py = 400;
      vy = 0;
      onGround = true;
    }

    // Ground
    if (py >= height - 20) {
      py = height - 20;
      vy = 0;
      onGround = true;
    }

    // Win condition
    if (px >= 700 && py <= 380) {
      levelComplete = true;
    }
  } else {
    textSize(40);
    fill(0, 200, 0);
    text("Level Complete!", width / 2, height / 2);
  }

  // Draw player
  fill(0, 0, 255);
  ellipse(px, py, 40, 40);
}

void drawPlatforms() {
  fill(150);
  rect(100, 520, 200, 20); // Platform 1
  rect(400, 420, 200, 20); // Platform 2
  rect(0, height - 20, width, 20); // Ground
}

void drawFinish() {
  fill(255, 0, 0);
  rect(700, 360, 20, 40);
}

void drawInstructions() {
  fill(0);
  textSize(16);
  text("Joystick to Move | Button to Jump", width / 2, 20);
}

// Read joystick input
void serialEvent(Serial port) {
  String data = port.readStringUntil('\n');
  if (data != null) {
    String[] parts = trim(data).split(",");
    if (parts.length == 3) {
      int xVal = int(parts[0]);
      int yVal = int(parts[1]);
      int btn = int(parts[2]);

      // X movement
      if (xVal < 400) vx = -5;
      else if (xVal > 600) vx = 5;
      else vx = 0;

      // Jump
      if (btn == 0 && onGround && !jumpPressed) {
        vy = -15;
        jumpPressed = true;
      }

      if (btn == 1) {
        jumpPressed = false;
      }
    }
  }
}
