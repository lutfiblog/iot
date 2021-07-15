<?php
    header("Access-Control-Allow-Origin: *");
    header("Content-Type: application/json; charset=UTF-8");
    header("Access-Control-Allow-Methods: POST");
    header("Access-Control-Max-button1: 3600");
    header("Access-Control-Allow-Headers: Content-Type, Access-Control-Allow-Headers, Authorization, X-Requested-With");
    
    include_once '../../config/database.php';
    include_once '../../class/dataClass.php';
    
    $database = new Database();
    $db = $database->getConnection();
    
    $item = new dataClass($db);
    
    $data = json_decode(file_get_contents("php://input"));
    
    $item->id = $data->id;
    
    // employee values
    $item->sensor1 = $data->sensor1;
    $item->sensor2 = $data->sensor2;
    $item->button1 = $data->button1;
    $item->button2 = $data->button2;
    $item->created = date('Y-m-d H:i:s');
    
    if($item->updateData()){
        echo json_encode("Data updated.");
    } else{
        echo json_encode("Data could not be updated");
    }
?>