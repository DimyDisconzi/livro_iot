<HTML><BODY>
<?php
$short_connect = new mysqli("mysql.hostinger.com.br", "u311824763_iot", "kedma256", "u311824763_iot");
			
if (!$_POST[Nome]){ // 1a Etapa: Se n�o tem os dados, verifica se uma nova tag foi lida...

	$sql = "SELECT * FROM Insercao
		WHERE DataHora > NOW() - INTERVAL 5 MINUTE
		ORDER BY DataHora DESC LIMIT 1";
	// Recupera a �ltima tag enviada
	$result = $short_connect->query($sql);
	if ((!$result) || ($result->num_rows == 0)){
		echo "N�o foi identificada nenhuma tag. Aproxime uma tag do leitor <BR>";
		header("Refresh:3"); // Tag n�o lida... Recarrega a p�gina at� a leitura.
	} else { // 2a Etapa: Tag lida, monta o formul�rio
		$row = $result->fetch_assoc();
		echo "<form action=insere.php method=POST>
		 <p>Nome: <input type=text name=Nome /></p>
		 <p>Documento: <input type=text name=Documento /></p>
		 <p>Tag: <input type=text name=Tag  value=" . $row['TAG'] . " /></p>	 
		 <p><input type=submit /></p>
		</form>";
	}
} else { // 3a Etapa: Se os dados j� foram enviados, insere no banco
	$sql = "INSERT INTO Usuarios VALUES ('". $_POST['Tag'] . "', '" . $_POST[Nome] . "', '" . $_POST[Documento] . "')";	
	//result is boolean for query other than SELECT, SHOW, DESCRIBE and EXPLAIN
	$result = $short_connect->query($sql);
	if ($result) 
		echo "Inser��o realizada com sucesso<BR>";
}
?>
</body></html>