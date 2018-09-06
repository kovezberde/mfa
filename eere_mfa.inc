<?php

class WsseAuthHeader extends SoapHeader {

    private $wss_ns = 'http://docs.oasis-open.org/wss/2004/01/oasis-200401-wss-wssecurity-secext-1.0.xsd';

    function __construct($user, $pass, $ns = null) {
        if ($ns) {
            $this->wss_ns = $ns;
        }

        $auth = new stdClass();
        $auth->Username = new SoapVar($user, XSD_STRING, NULL, $this->wss_ns, NULL, $this->wss_ns);
        $auth->Password = new SoapVar($pass, XSD_STRING, NULL, $this->wss_ns, NULL, $this->wss_ns);

        $username_token = new stdClass();
        $username_token->UsernameToken = new SoapVar($auth, SOAP_ENC_OBJECT, NULL, $this->wss_ns, 'UsernameToken', $this->wss_ns);

        $security_sv = new SoapVar(
                new SoapVar($username_token, SOAP_ENC_OBJECT, NULL, $this->wss_ns, 'UsernameToken', $this->wss_ns), SOAP_ENC_OBJECT, NULL, $this->wss_ns, 'Security', $this->wss_ns);
        parent::__construct($this->wss_ns, 'Security', $security_sv, true);
    }
}

class MFAAuthentication {

  public function __construct($uid, $user, $email, $param, $softToken) {
        $arguments = func_get_args();
        $username = variable_get('username', NUL);
        $password = variable_get('password', NULL);
        $wsdl = variable_get('url', NULL);
        $basic = variable_get('basic_url', NULL);
        $this->username = $username;
        $this->password = $password;
        $this->wsdl = $wsdl;
        $this->basic = $basic;
        $this->uid = $uid;
        $this->email = $email;
        $this->user = $user;
        $this->softToken = $softToken;
        $this->param = $param;

        
       
        //Reset Soft Token Setup
       if (sizeof(func_get_args()) == 1) {    
        $this->options = array(
        'appUserId' => $this->uid,
      );
       
      }
        //Create Soft Token URL
        if (sizeof(func_get_args()) == 4) {   
        $this->options = array(
        'appUserId' => $this->uid,
        'userName' => $this->user,
        'email' => $this->email,
        'defaultSoftTokenTypeId' => '4',
        'userIPAddress' => $_SERVER["REMOTE_ADDR"],
        'returnUrl' => $this->param,
      );
       
      }
     
     //Request Soft Token 
     if (sizeof(func_get_args()) == 3) { 
       $this->options = array (
        'appUserId' => $this->uid,
        'email' => $arguments[1],
        'softToken' =>  $arguments[3], 
        'softTokenTypeId' => $arguments[2],
      );
     }  
     
    //Validate Soft Token
    if (sizeof(func_get_args()) == 5) {
        $this->options = array (
        'appUserId' => $this->uid,
        'softToken' => $arguments[2],
        'softTokenTypeId' => $arguments[1],
      );
    }
 } 

   public function _call() {
       
        $wsse_header = new WsseAuthHeader($this->username, $this->password);
        $client = new SoapClient($this->wsdl, array(
            "trace" => 1,
            "exceptions" => 1,
          )
        );
        $client->__setLocation($this->basic);
        $client->__setSoapHeaders(array($wsse_header));

        return $client;
       
   } 
   
function create_soft_token_setup_url() {

       $client = $this->_call();
       
        try {
        $results = $client->CreateSoftTokenSetupUrl($this->options);
        }
        
        catch (SoapFault $e ){
         form_set_error('error', t('Error'.$e.$client->__getLastRequest()));
        
        }

        return $results->CreateSoftTokenSetupUrlResult;

}


 function request_soft_token() {
       
       $client = $this->_call();
       
       try {
        $results = $client->RequestSoftToken($this->options);

        }
        catch (SoapFault $e ){
         form_set_error('error', t('Error'.$e.$client->__getLastRequest()));
        
        }
        return $results->RequestSoftTokenResult;
        //return $this->options;
   }



   function validate_soft_token() {

       $client = $this->_call();
       
        try {
        $results = $client->ValidateSoftToken($this->options);

        }
        catch (SoapFault $e ){
         form_set_error('error', t('Error'.$e.$client->__getLastRequest()));
        
        }
        return $results->ValidateSoftTokenResult;
        //return $this->options;
   }
   
      
function validate_soft_token_setup() {

       $client = $this->_call();
       
        try {
        $results = $client->ValidateSoftTokenSetup($this->options);

        }
        catch (SoapFault $e ){
         form_set_error('error', t('Error'.$e.$client->__getLastRequest()));
        
        }
        return $results->ValidateSoftTokenSetupResult;
  
   }
   
   
function reset_soft_token_setup() {

       $client = $this->_call();
       
        try {
         $client->ResetSoftTokenSetup($this->options);

        }
        catch (SoapFault $e ){
         form_set_error('error', t('Error'.$e.$client->__getLastRequest()));
        
        }
  
   }
}
