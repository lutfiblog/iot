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

    $item->id = isset($_GET['id']) ? $_GET['id'] : die();
  
    $item->getSingleData();

    if($item->sensor1 != null){
        // create array
        $emp_arr = array(
            "id" =>  $item->id,
            "sensor1" => $item->sensor1,
            "sensor2" => $item->sensor2,
            "button1" => $item->button1,
            "button2" => $item->button2,
            "created" => $item->created
        );
      
        http_response_code(200);
        echo json_encode($emp_arr);
    }
      
    else{
        http_response_code(404);
        echo json_encode("data not found.");
    }
?>