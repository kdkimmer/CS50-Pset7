<?php

    // configuration
    require("../includes/config.php");

    // if form was submitted
    if ($_SERVER["REQUEST_METHOD"] == "POST")
    {
        // validate the name
        if (empty($_POST["symbol"]))
        {
            apologize("Please enter the stock symbol.");
        }
        // validate the stock amt
        if (empty($_POST["shares"]) || !is_numeric($_POST["shares"]) || !preg_match("/^\d+$/", $_POST["shares"]))
        {
            apologize("Please enter the correct amount of shares.");
        }
        // Query Yahoo
        {
            $stock = lookup($_POST["symbol"]);
        }
        // Check if we returned nothing
        if ($stock === false)
        {
            apologize("The stock symbol was invalid.");
        }
        else
        {
            $value = $stock["price"] * $_POST["shares"];
            
  
            // check the amt of cash
            $cash = query("SELECT cash FROM users WHERE id = ?", $_SESSION["id"]);
            if ($cash < $value)
            {
                apologize("You do not have sufficient amount of money in deposits.");
            }
            else
            {
                // insert the bought stock into database
                $query = query("INSERT INTO portfolio(id, symbol, shares) VALUES (?,?,?)
                ON DUPLICATE KEY UPDATE shares = shares + VALUES(shares)",
                $_SESSION["id"], strtoupper($stock["symbol"]), $_POST["shares"]);
                if ($query === false)
                {
                    apologize("Error while buying your shares.");
                }
                
                // update cash
                $query = query("UPDATE users SET cash = cash - ? WHERE id = ?", $value, $_SESSION["id"]);
                if ($query === false)
                {
                    apologize("Error while buying your shares.");
                }
            
               $_SESSION["cash"] -= $value;
            
                // log history
                $query = query("INSERT INTO history(id, transaction, symbol, shares, price) VALUES (?,?,?,?,?)",$_SESSION["id"], "Buy", strtoupper($stock["symbol"]),$_POST["shares"], $stock["price"]);
           
                // redirect to portfolio
                redirect("index.php");
            }
        }          
    }    
    else
    {
        render("buy_form.php", ["title" => "Buy"]);
    }
?>
