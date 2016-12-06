var nodeMcuIp;
var camAngle = 90;
var isCarConnect = false;

function checkConnection() {
  var request = new XMLHttpRequest();

  request.open('GET', 'http://blynk-cloud.com/d47461487fe24c2bac9d7b04d72c9439/isHardwareConnected');

  request.onreadystatechange = function () {
    if (this.readyState === 4) {
      console.log('Status:', this.status);
      console.log('Headers:', this.getAllResponseHeaders());
      console.log('Body:', this.responseText);
      return this.responseText == 'true';
    }
  };

  request.send()
}
function clickMove(element) {
  if($('.pressing').length === 0) {
    var dir = element.attr('id');
    // $.get(nodeMcuIp, {DIR:dir});
    var pin = getPin(dir);
    $.get('http://blynk-cloud.com/d47461487fe24c2bac9d7b04d72c9439/update/v' + pin + '?value=1');
    $('#' + dir).addClass('pressing');
  }
}

function getPin(dir) {
  var pin = null;
  if(dir === 'UP') {
    pin = 3;
  } else if(dir === 'DOWN') {
    pin = 4;
  } else if(dir === 'LEFT') {
    pin = 5;
  } else {
    pin = 6;
  }
  return pin;
}

function still() {
  $('.wheel.pressing').removeClass('pressing');
  // $.get(nodeMcuIp, {DIR:'STILL'});
  $.get('http://blynk-cloud.com/d47461487fe24c2bac9d7b04d72c9439/update/v7?value=1');
}

function pressMove(element) {
  if($('.pressing.wheel').length === 0) {
    var dir = element.attr('id');
    // $.get(nodeMcuIp, {DIR:dir});
    var pin = getPin(dir);
    $.get('http://blynk-cloud.com/d47461487fe24c2bac9d7b04d72c9439/update/v' + pin + '?value=1');
    element.addClass('pressing');
  }
}

function readIpFromInput() {
  nodeMcuIp = $('input.ip_input').val();
  nodeMcuIp = 'http://' + nodeMcuIp;
  $('input.ip_input').val('');
  $('#current_ip').text('Current IP: ' + nodeMcuIp);
}

function panCam(element) {
  if($('.pressing.cam').length == 0) {
    element.addClass('pressing');
    var dir = element.attr('id');
    // $.get(nodeMcuIp, {CAM:dir});
    if(dir == 'RIGHT') {
      camAngle += 5;
    } else {
      camAngle -= 5;
    }
    $.get('http://blynk-cloud.com/d47461487fe24c2bac9d7b04d72c9439/update/v2?value=' + camAngle);
  }
}

function stillCam() {
  $('.pressing.cam').removeClass('pressing');
  // $.get(nodeMcuIp, {CAM:'STILL'});
  // $.get('http://blynk-cloud.com/d47461487fe24c2bac9d7b04d72c9439/update/pin?value=1');
}


$(document).ready(function(){
  if(checkConnection()) {
    $('#connect').text('connected');
    isCarConnect = true;
  } else {
    $('#connect').text('not connect');
    isCarConnect = false;
  }
  $('button.ip_input').click(function() {
    readIpFromInput();
    console.log(nodeMcuIp);
  });
  $(".wheel").mousedown(function(){
    clickMove($(this));
  });
  $(document).mouseup(function(){
    still();
  });
  $(document).on( "keydown", function( event ) {
    var key = String.fromCharCode(event.keyCode);
    if(!$('input.ip_input').is(':focus')) {
      if (key === 'W') {
        pressMove($('.wheel#UP'));
      } else if (key === 'S') {
        pressMove($('.wheel#DOWN'))
      } else if (key === 'A') {
        pressMove($('.wheel#LEFT'))
      } else if (key === 'D') {
        pressMove($('.wheel#RIGHT'))
      } else if (event.keyCode === 190) {  //camera right
        panCam($('.cam#RIGHT'));
      } else if (event.keyCode === 188) {  //camera left
        panCam($('.cam#LEFT'));
      }
    } else {
      if(key === '\r') {
        readIpFromInput();
        console.log(nodeMcuIp);
      }
    }
  });
  $(document).on( "keyup", function(event) {
    var key = String.fromCharCode(event.keyCode);
    if(key === 'W' || key === 'S' || key === 'A' || key === 'D') {
      still();
    } else if(event.keyCode === 190 || event.keyCode === 188) {
      stillCam();
    }
  });
});
