

    <a href="quote.php">Quote</a>
    <a href="buy.php">Buy</a>
    <a href="sell.php">Sell</a>
    <a href="index.php">Portfolio</a>
    <a href="deposit.php">Deposit</a>
    <a href="logout.php"><strong>Log Out</strong></a>

<table class="table">

    <thead>
        <tr>
            <th>Transaction Type</th>
            <th>Date/Time</th>
            <th>Symbol</th>
            <th>Shares</th>
            <th>Price</th>
            <th>Total</th>
        </tr>
    </thead>


    <tbody>
    <?php
            foreach ($table as $row)    
        {   
            echo("<tr>");
            echo("<td>" . $row["transaction"] . "</td>");
            echo("<td>" . date('m/d/y, g:i A',strtotime($row["datetime"])) . "</td>");
            echo("<td>" . $row["symbol"] . "</td>");
            echo("<td>" . $row["shares"] . "</td>");
            echo("<td>$" . money_format("%i",$row["price"]) . "</td>");
            echo("<td>$" . money_format("%i",$row["price"] * $row["shares"]) ."</td>");
            echo("</tr>");
        }
    ?>

    <tr>
        <td class="hello" colspan="4"><strong>CASH</strong></td>
        <td class="hello"><strong>$<?= money_format("%i",$cash[0]["cash"])?></strong></td>
    </tr>

    </tbody>
    
</table>


