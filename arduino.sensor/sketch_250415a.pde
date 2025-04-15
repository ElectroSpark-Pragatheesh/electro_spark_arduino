import processing.serial.*;
import java.util.ArrayList;

Serial myPort;

int angle;
float distance;

ArrayList<EchoLine> echoLines = new ArrayList<EchoLine>();

void setup() {
  size(800, 600);
  println(Serial.list());
  myPort = new Serial(this, Serial.list()[0], 9600);
  myPort.bufferUntil('\n');
}

void draw() {
  background(0);
  translate(width / 2, height);
  stroke(0, 255, 0);
  noFill();

  // Radar rings
  for (int r = 100; r <= 400; r += 100) {
    ellipse(0, 0, r * 2, r * 2);
  }

  // Angle lines
  for (int a = 0; a <= 180; a += 30) {
    float x = cos(radians(a)) * 400;
    float y = -sin(radians(a)) * 400;
    line(0, 0, x, y);
  }

  // Green sweep line
  float sweepX = cos(radians(angle)) * 400;
  float sweepY = -sin(radians(angle)) * 400;
  stroke(0, 255, 0, 180);
  line(0, 0, sweepX, sweepY);

  // Draw red echo lines (past object detections)
  for (int i = echoLines.size() - 1; i >= 0; i--) {
    EchoLine e = echoLines.get(i);
    if (millis() - e.timestamp < 2000) { // Show for 2 seconds
      stroke(255, 0, 0);
      float x = cos(radians(e.angle)) * e.length;
      float y = -sin(radians(e.angle)) * e.length;
      line(0, 0, x, y);
    } else {
      echoLines.remove(i); // remove old lines
    }
  }

  // Text info
  fill(0, 255, 0);
  textSize(16);
  textAlign(LEFT);
  text("Electro Spark Radar", -width / 2 + 10, 20 - height);
  text("Angle: " + angle + "°", -width / 2 + 10, 40 - height);
  text("Distance: " + nf(distance, 0, 2) + " cm", -width / 2 + 10, 60 - height);
}

void serialEvent(Serial p) {
  String data = trim(p.readStringUntil('\n'));
  if (data != null) {
    String[] parts = split(data, ',');
    if (parts.length == 2) {
      angle = int(parts[0]);
      distance = float(parts[1]);

      if (distance > 2 && distance < 200) {
        float lineLength = map(distance, 0, 200, 0, 400);
        echoLines.add(new EchoLine(angle, lineLength, millis()));
      }
    }
  }
}

class EchoLine {
  int angle;
  float length;
  int timestamp;

  EchoLine(int a, float l, int t) {
    angle = a;
    length = l;
    timestamp = t;
  }
}
import processing.serial.*;
import java.util.ArrayList;

Serial myPort;

int angle;
float distance;

ArrayList<EchoLine> echoLines = new ArrayList<EchoLine>();

void setup() {
  size(800, 600);
  println(Serial.list());
  myPort = new Serial(this, Serial.list()[0], 9600);
  myPort.bufferUntil('\n');
}

void draw() {
  background(0);
  translate(width / 2, height);
  stroke(0, 255, 0);
  noFill();

  // Radar rings
  for (int r = 100; r <= 400; r += 100) {
    ellipse(0, 0, r * 2, r * 2);
  }

  // Angle lines
  for (int a = 0; a <= 180; a += 30) {
    float x = cos(radians(a)) * 400;
    float y = -sin(radians(a)) * 400;
    line(0, 0, x, y);
  }

  // Green sweep line
  float sweepX = cos(radians(angle)) * 400;
  float sweepY = -sin(radians(angle)) * 400;
  stroke(0, 255, 0, 180);
  line(0, 0, sweepX, sweepY);

  // Draw red echo lines (past object detections)
  for (int i = echoLines.size() - 1; i >= 0; i--) {
    EchoLine e = echoLines.get(i);
    if (millis() - e.timestamp < 2000) { // Show for 2 seconds
      stroke(255, 0, 0);
      float x = cos(radians(e.angle)) * e.length;
      float y = -sin(radians(e.angle)) * e.length;
      line(0, 0, x, y);
    } else {
      echoLines.remove(i); // remove old lines
    }
  }

  // Text info
  fill(0, 255, 0);
  textSize(16);
  textAlign(LEFT);
  text("Electro Spark Radar", -width / 2 + 10, 20 - height);
  text("Angle: " + angle + "°", -width / 2 + 10, 40 - height);
  text("Distance: " + nf(distance, 0, 2) + " cm", -width / 2 + 10, 60 - height);
}

void serialEvent(Serial p) {
  String data = trim(p.readStringUntil('\n'));
  if (data != null) {
    String[] parts = split(data, ',');
    if (parts.length == 2) {
      angle = int(parts[0]);
      distance = float(parts[1]);

      if (distance > 2 && distance < 200) {
        float lineLength = map(distance, 0, 200, 0, 400);
        echoLines.add(new EchoLine(angle, lineLength, millis()));
      }
    }
  }
}

class EchoLine {
  int angle;
  float length;
  int timestamp;

  EchoLine(int a, float l, int t) {
    angle = a;
    length = l;
    timestamp = t;
  }
}
