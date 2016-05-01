#!/usr/bin/env node
var exec = require('child_process').execFile;

var turn = 0;
var board = [' ',' ',' ',' ',' ',' ',
             ' ',' ',' ',' ',' ',' ',
             ' ',' ',' ',' ',' ',' ',
             ' ',' ',' ',' ',' ',' ',
             ' ',' ',' ',' ',' ',' ',
             ' ',' ',' ',' ',' ',' '];

function boardStr() {
  var s = "";
  var delim = "";
  for(var i=0; i<6; i++) {
    s += delim + board.slice(i*6,i*6+6).join("").replace(new RegExp(" ", 'g'), "-");
    delim = "\n";
  }
  return s;
}

function getWinner() {
  var lines = [];
  // horizontal
  for(var y=0; y<6; y++) {
    lines = lines.concat(
      board.slice(y*6,y*6+5).join(""),
      board.slice(y*6+1,y*6+6).join(""));
  }
  // vertical
  for(var x=0; x<6; x++) {
    for(var starty=0; starty<=1; starty++) {
      var line = "";
      for(var y=starty; y<starty+5; y++) {
        line += board[x+y*6];
      }
      lines = lines.concat(line);
    }
  }
  // \ lines
  for(var i=0;i<4;i++) {
    var x = [0,1,6,7][i];
    var line = "";
    for(var y=0;y<5;y++) {
      line += board[x + y*7];
    }
    lines = lines.concat(line);
  }
  // / lines
  for(var i=0;i<4;i++) {
    var x = [4,5,10,11][i];
    var line = "";
    for(var y=0;y<5;y++) {
      line += board[x + y*5];
    }
    lines = lines.concat(line);
  }
  var orderCanWin = false;
  for(var i=0; i<lines.length; i++) {
    var line = lines[i];
    if (line === 'XXXXX' || line === 'OOOOO') {
      return 'ORDER'
    }
    if (line.indexOf("X") < 0 || line.indexOf("O") < 0){
      orderCanWin = true;
    }
  }
  return orderCanWin ? undefined : 'CHAOS';
}

function takeTurn() {
  var cmd = ["./order", "./chaos"][turn];
  var state = board.join("") + ['o','c'][turn];
  console.log("\n\nPlaying as",["order","chaos"][turn],"'" + state + "'");
  exec(cmd, [state], function(err, data) {
    if (err) {
      return console.log(err);
    }
    var move = data.toString().trim();
    console.log("Move is",move);
    var piece = move[0];
    var position = parseInt(move.substr(1));
    board[position] = piece;
    console.log("Board:", "\n" + boardStr());
    var winner = getWinner();
    if (winner) {
      return console.log("Game over", winner, "wins");
    }
    turn = 1-turn;
    setTimeout(takeTurn, 1000);
  });
}

takeTurn();