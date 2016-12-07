// var nodeMcuIp;
var camAngle = 90;
var isCarConnect = false;
var auth_token = 'd47461487fe24c2bac9d7b04d72c9439';

function checkConnection() {
  var request = new XMLHttpRequest();

  request.open('GET', 'http://blynk-cloud.com/' + auth_token + '/isHardwareConnected');

  request.onreadystatechange = function () {
    if (this.readyState === 4) {
      console.log('Status:', this.status);
      console.log('Headers:', this.getAllResponseHeaders());
      console.log('Body:', this.responseText);
      if(this.responseText == 'true') {
        $('p.connect').text('connected');
        $('button.connect.status').css('background-color', 'green');
      } else {
        $('p.connect').text('not connect');
        $('button.connect.status').css('background-color', 'red');
      }
    }
  };

  request.send()
}
function clickMove(element) {
  if($('.wheel.pressing').length === 0) {
    var dir = element.attr('name');
    var pin = getPin(dir);
    if(pin == null) {
      return;
    }
    $.get('http://blynk-cloud.com/' + auth_token + '/update/v' + pin + '?value=1');
    $('.wheel.' + dir).addClass('pressing');
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
  } else if(dir === 'RIGHT') {
    pin = 6;
  }
  return pin;
}

function still() {
  removePressing($('.wheel.pressing'));
  // $.get(nodeMcuIp, {DIR:'STILL'});
  $.get('http://blynk-cloud.com/' + auth_token +'/update/v7?value=1');
}

function pressMove(element) {
  if($('.pressing.wheel').length === 0) {
    var dir = element.attr('name');
    // $.get(nodeMcuIp, {DIR:dir});
    var pin = getPin(dir);
    $.get('http://blynk-cloud.com/' + auth_token +'/update/v' + pin + '?value=1');
    element.addClass('pressing');
  }
}

function readAuthTokenFromInput() {
  var input = $('input.ip_input').val();
  if(input === '') {
    input = $('input.ip_input.mobile').val();
  }
  if(input !== '') {
    auth_token = input;
  } else {
    auth_token = 'd47461487fe24c2bac9d7b04d72c9439';
  }
  $('input.ip_input').val('');
  $('.current_auth_token').text('Auth Token: ' + auth_token);
  $('.remove_auth').css('display', 'inline');
  checkConnection();
}

function panCam(element) {
  if($('.pressing.cam').length == 0) {
    element.addClass('pressing');
    var dir = element.attr('name');
    // $.get(nodeMcuIp, {CAM:dir});
    if(dir == 'RIGHT' && camAngle > 0) {
      camAngle -= 45;
    } else if (dir == 'LEFT' && camAngle < 180){
      camAngle += 45;
    }
    $.get('http://blynk-cloud.com/' + auth_token +'/update/v2?value=' + camAngle);
  }
}

function resetCam() {
  $.get('http://blynk-cloud.com/' + auth_token +'/update/v2?value=90');
}

function removePressing(element) {
  element.removeClass('pressing');
}

function removeAuth() {
  auth_token = '';
  $('.current_auth_token').text('');
  $('.remove_auth').css('display', 'none');
  checkConnection();
}


$(document).ready(function(){
  checkConnection();
  $('button.connect.refresh').click(function() {
    $('p.connect').text('');
    resetCam();
    checkConnection();
  });
  $('button.ip_input').click(function() {
    readAuthTokenFromInput();
    console.log(auth_token);
  });
  $(".wheel.btn").mousedown(function(){
    clickMove($(this));
  });
  $(".cam.btn").mousedown(function() {
    panCam($(this));
  });
  $('.remove_auth').click(function() {
    removeAuth();
  });
  $('button.resetCam').click(function() {
    resetCam();
  });
  $(document).mouseup(function(){
    still();
    removePressing($('.cam'))
  });
  $(document).on( "keydown", function( event ) {
    var key = String.fromCharCode(event.keyCode);
    if(!$('input.ip_input').is(':focus')) {
      if (key === 'W') {
        pressMove($('.wheel.UP'));
      } else if (key === 'S') {
        pressMove($('.wheel.DOWN'))
      } else if (key === 'A') {
        pressMove($('.wheel.LEFT'))
      } else if (key === 'D') {
        pressMove($('.wheel.RIGHT'))
      } else if (event.keyCode === 190) {  //camera right
        panCam($('.cam.RIGHT'));
      } else if (event.keyCode === 188) {  //camera left
        panCam($('.cam.LEFT'));
      }
    } else {
      if(key === '\r') {
        readAuthTokenFromInput();
        console.log(auth_token);
      }
    }
  });
  $(document).on( "keyup", function(event) {
    var key = String.fromCharCode(event.keyCode);
    if(key === 'W' || key === 'S' || key === 'A' || key === 'D') {
      still();
    } else if(event.keyCode === 190 || event.keyCode === 188) {
      removePressing($('.pressing.cam'));
    }
  });
});
