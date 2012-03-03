/*
   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#define PLAYER_A_BUTTON 13
#define PLAYER_A_LIGHT   9
#define PLAYER_B_BUTTON 12
#define PLAYER_B_LIGHT   8
#define PLAYER_C_BUTTON 11
#define PLAYER_C_LIGHT   7
#define PLAYER_D_BUTTON 10
#define PLAYER_D_LIGHT   6

#define UNLOCK_BUTTON 4
#define BUZZER 2

#define ENABLE_PULLUP HIGH

bool someone_won = false;

void player_buttonlight_startup_test_flash()
{
  digitalWrite(PLAYER_A_LIGHT, HIGH);
  digitalWrite(PLAYER_B_LIGHT, HIGH);
  digitalWrite(PLAYER_C_LIGHT, HIGH);
  digitalWrite(PLAYER_D_LIGHT, HIGH);
  delay(1000);
  digitalWrite(PLAYER_A_LIGHT, LOW);
  digitalWrite(PLAYER_B_LIGHT, LOW);
  digitalWrite(PLAYER_C_LIGHT, LOW);
  digitalWrite(PLAYER_D_LIGHT, LOW);  
}

void play_winner_buzz()
{
  tone(BUZZER, 440, 200);
  delay(210);
  tone(BUZZER, 440*3/2, 200);
  delay(210);
}

void setup()
{
  Serial.begin(9600);
  Serial.println("GettuBest");
  
  pinMode(PLAYER_A_LIGHT,  OUTPUT);
  pinMode(PLAYER_A_BUTTON, INPUT);
  digitalWrite(PLAYER_A_BUTTON, ENABLE_PULLUP); 

  pinMode(PLAYER_B_LIGHT,  OUTPUT);
  pinMode(PLAYER_B_BUTTON, INPUT);
  digitalWrite(PLAYER_B_BUTTON, ENABLE_PULLUP); 

  pinMode(PLAYER_C_LIGHT,  OUTPUT);
  pinMode(PLAYER_C_BUTTON, INPUT);
  digitalWrite(PLAYER_C_BUTTON, ENABLE_PULLUP); 

  pinMode(PLAYER_D_LIGHT,  OUTPUT);
  pinMode(PLAYER_D_BUTTON, INPUT);
  digitalWrite(PLAYER_D_BUTTON, ENABLE_PULLUP); 

  pinMode(UNLOCK_BUTTON, INPUT);
  digitalWrite(UNLOCK_BUTTON, ENABLE_PULLUP); 

  player_buttonlight_startup_test_flash();
  
  play_winner_buzz();
  
  someone_won = false;
}

void notify_winner(int player)
{
  someone_won = true;
  digitalWrite(player, HIGH);  

  play_winner_buzz();
}

void loop()
{
  if(!digitalRead(UNLOCK_BUTTON))
  {
    Serial.println("Unlocking");
    someone_won = false;
    digitalWrite(PLAYER_A_LIGHT, LOW);
    digitalWrite(PLAYER_B_LIGHT, LOW);
    digitalWrite(PLAYER_C_LIGHT, LOW);
    digitalWrite(PLAYER_D_LIGHT, LOW);  
  }  
  
  if(someone_won)
    return;
  
  // get status of all player buttons
  int player_a = !digitalRead(PLAYER_A_BUTTON);
  int player_b = !digitalRead(PLAYER_B_BUTTON);
  int player_c = !digitalRead(PLAYER_C_BUTTON);
  int player_d = !digitalRead(PLAYER_D_BUTTON);
 
  // check if anyone won, set its light
  if (player_a)
  {
    Serial.println("We have a winner: A");
    notify_winner(PLAYER_A_LIGHT);
    return; 
  }
  if (player_b)
  {
    Serial.println("We have a winner: B");
    notify_winner(PLAYER_B_LIGHT);
    return; 
  } 
  if (player_c)
  {
    Serial.println("We have a winner: C");
    notify_winner(PLAYER_C_LIGHT);
    return; 
  } 
  if (player_d)
  {
    Serial.println("We have a winner: D");
    notify_winner(PLAYER_D_LIGHT);
    return; 
  } 
 
}
