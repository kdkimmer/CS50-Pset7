<?php

    // configuration
    require("../includes/config.php");

    // if form was submitted
    if ($_SERVER["REQUEST_METHOD"] == "POST")
    {
        // validate the amount
        if (empty($_POST["amount"]))
        {
            apologize("Please enter a valid amount to deposit.");
        }
        else if (!preg_match("/^\d+$/", $_POST["amount"])== false)
        {
            apologize("Please enter a valid amount to deposit.");
        } 
        
        // update cash
        $query = query("UPDATE users SET cash = cash + ? WHERE id = ?",$_POST["amount"] , $_SESSION["id"]);
                
        // redirect to portfolio
        redirect("index.php");
             
    }    
    else
    {
        render("deposit_form.php", ["title" => "Deposit"]);
    }
?>
