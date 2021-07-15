<?php
    header("Access-Control-Allow-Origin: *");
    header("Content-Type: application/json; charset=UTF-8");
    
    include_once '../../config/database.php';
    include_once '../../class/dataClass.php';

    $database = new Database();
    $db = $database->getConnection();

    $items = new dataClass($db);

    $stmt = $items->getData();
    $itemCount = $stmt->rowCount();


    echo json_encode($itemCount);

    if($itemCount > 0){
        
        $dataArr = array();
        $dataArr["body"] = array();
        $dataArr["itemCount"] = $itemCount;

        while ($row = $stmt->fetch(PDO::FETCH_ASSOC)){
            extract($row);
            $e = array(
                "id" => $id,
                "sensor1" => $sensor1,
                "sensor2" => $sensor2,
                "button1" => $button1,
                "button2" => $button2,
                "created" => $created
            );

            array_push($dataArr["body"], $e);
        }
        echo json_encode($dataArr);
    }

    else{
        http_response_code(404);
        echo json_encode(
            array("dataapi" => "No record found.")
        );
    }
?>