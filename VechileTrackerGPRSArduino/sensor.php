<?php
session_start();

class stdObject {

    public function __construct(array $arguments = array()) {
        if (!empty($arguments)) {
            foreach ($arguments as $property => $argument) {
                $this->{$property} = $argument;
            }
        }
    }

    public function __call($method, $arguments) {
        $arguments = array_merge(array("stdObject" => $this), $arguments); // Note: method argument 0 will always referred to the main class ($this).
        if (isset($this->{$method}) && is_callable($this->{$method})) {
            return call_user_func_array($this->{$method}, $arguments);
        } else {
            throw new Exception("Fatal error: Call to undefined method stdObject::{$method}()");
        }
    }

}

class settingsClass{
    var $lat;
    var $lag;
}

$settings = new stdObject();

$allnull = 1;

$jsondata = file_get_contents('settings.txt');
$settings = json_decode($jsondata);

if(isset($_GET['lat'])){
    $settings->lat =$_GET['lat'];
    $allnull = 0;
}

if(isset($_GET['lag'])){
    $settings->lag =$_GET['lag'];
    $allnull = 0;
}

if($allnull == 0){
    $fp = fopen('settings.txt', 'w');
    fwrite($fp, json_encode($settings));
    fclose($fp);
}

if(isset($_GET['json'])){
    echo json_encode($settings);
}
else{
    echo $settings->lat . "," . $settings->lag;
}

?>