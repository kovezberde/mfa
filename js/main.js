(function ($) {
$(document).ready(function($) {
$pathname = window.location.pathname;
$str = $pathname.split('/');
$arg = $str[$str.length-3];
$setup = $str[$str.length-2];
$('#eere-mfa-form').attr('action', '');
$('#edit-token').focus();
$('#edit-reset-button').css('display', 'none');

//For email authentication
if ($arg === '4') {
$('#edit-radio-buttons-email-auth').attr('checked', true);
}
//For email sms
if ($arg === '2') {
$('#edit-radio-buttons-sms').attr('checked', true);
}
//For email app
if ($arg === '1') {
$('#edit-radio-buttons-app').attr('checked', true);
}

//For email authentication
if ($setup === '4') {
$('#edit-radio-buttons-sms').attr('disabled',true);
$('#edit-radio-buttons-app').attr('disabled',true);
}
//For email sms
if ($setup === '6') {
$('#edit-radio-buttons-app').attr('disabled',true);
}
//For email app
if ($setup === '5') {
$('#edit-radio-buttons-sms').attr('disabled',true);
}
$('.reset').click(function () {
    $('#edit-reset-button').trigger( "click" );
});
  });
})
(jQuery);
