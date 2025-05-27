import processing.serial.*;

Serial port;

int crossX = 320;
int crossY = 240;
int targetX, targetY;
int score = 0;
int timeLeft = 30; // seconds
boolean hit = false;
PFont font;

void setup() {
  size(640, 480);
  frameRate(60);

  // Serial
  printArray(Serial.list());
  port = new Serial(this, Serial.list()[0], 9600);
  port.bufferUntil('\n');

  // Font
  font = createFont("Arial", 20, true);

  // Initial target
  spawnNewTarget();

  // Timer
  new java.util.Timer().scheduleAtFixedRate(
    new java.util.TimerTask() {
      public void run() {
        if (timeLeft > 0) timeLeft--;
      }
    }, 1000, 1000
  );
}

void draw() {
  background(0);

  // Target
  fill(hit ? color(0, 255, 0) : color(255, 0, 0));
  noStroke();
  ellipse(targetX, targetY, 40, 40);

  // Crosshair
  stroke(255);
  line(crossX - 10, crossY, crossX + 10, crossY);
  line(crossX, crossY - 10, crossX, crossY + 10);

  // Score & Time
  fill(255);
  textFont(font);
  text("Score: " + score, 20, 30);
  text("Time: " + timeLeft, 540, 30);

  if (timeLeft <= 0) {
    textAlign(CENTER);
    textSize(36);
    fill(255, 255, 0);
    text("GAME OVER", width / 2, height / 2);
    noLoop(); // stop game
  }
}

void spawnNewTarget() {
  targetX = int(random(50, width - 50));
  targetY = int(random(50, height - 50));
  hit = false;
}

void serialEvent(Serial port) {
  String data = port.readStringUntil('\n');
  if (data != null && timeLeft > 0) {
    String[] parts = trim(data).split(",");
    if (parts.length == 3) {
      int rawX = int(parts[0]);
      int rawY = int(parts[1]);
      int button = int(parts[2]);

      crossX += map(rawX, 0, 1023, -5, 5);
      crossY += map(rawY, 0, 1023, -5, 5);

      crossX = constrain(crossX, 0, width);
      crossY = constrain(crossY, 0, height);

      if (button == 0 && !hit) {
        float d = dist(crossX, crossY, targetX, targetY);
        if (d < 25) {
          score++;
          hit = true;
          spawnNewTarget();
        }
      }
    }
  }
}
