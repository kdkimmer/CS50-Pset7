<?php

    // configuration
    require("../includes/config.php");  
    
    // if form is submitted - do price checks and calculate - then update history
    if ($_SERVER["REQUEST_METHOD"] == "POST") 
    {
        // validate the name
        if (empty($_POST["symbol"]))
        {
            apologize("Please enter the stock symbol.");
        }
               
        $stock = lookup($_POST["symbol"]);
        
        $shares = query("SELECT shares FROM portfolio WHERE id = ? AND symbol = ?", $_SESSION["id"],  strtoupper($_POST["symbol"]));
        
        $value = $stock["price"] * $shares[0]["shares"];
        
        query("UPDATE users SET cash = cash + ? WHERE id = ?", $value, $_SESSION["id"]);
                     
        query("INSERT INTO history (id, transaction, symbol, shares, price) VALUES (?, ?, ?, ?, ?)", $_SESSION["id"], "Sell",  strtoupper($_POST["symbol"]), $shares[0]["shares"], $stock["price"]);
    
        // Delete old portfolio info
        query("DELETE FROM portfolio WHERE id = ? AND symbol = ?", $_SESSION["id"],  strtoupper($_POST["symbol"]));
        // redirect to portfolio 
        redirect("index.php");
    }
    
    // if form hasn't been submitted
    else
    {
        // query user's portfolio
        $rows = query("SELECT symbol FROM portfolio WHERE id = ?", $_SESSION["id"]); 

        // create new array to store stock symbols
        $stocks = [];

        // for each of user's stocks, save stock symbol & add stock symbol to the new array
        foreach ($rows as $row) 
        {   
            $stock = $row["symbol"];         
            $stocks[] = $stock;       
        }    

        //render sell form
        render("sell_form.php", ["title" => "Sell Form", "stocks" => $stocks]);  
    }   
?>
