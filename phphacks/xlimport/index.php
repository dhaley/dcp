<html>
<body>
  <form enctype="multipart/form-data" action="import.php" method="post">
    Excel XML file:
        <input type="hidden" name="MAX_FILE_SIZE" value="2000000" />
    <input type="file" name="file" /><br/>
    <input type="submit" value="Upload" />
  </form>
</body>
</html>
