<%@ Page Language="C#" AutoEventWireup="true" CodeFile="TestCSS.aspx.cs" Inherits="TestCSS" %>

<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Transitional//EN" "http://www.w3.org/TR/xhtml1/DTD/xhtml1-transitional.dtd">

<html xmlns="http://www.w3.org/1999/xhtml" >
<head runat="server">
    <title>Untitled Page</title>
  <link href="StyleSheet.css" rel="stylesheet" type="text/css" />
</head>
<body>
    <form id="form1" runat="server">
    <div>
<h1>This will appear in bold blue italics</h1>
    <p>Normal text.</p>
    <h2 style="color: red; background: green;">
      This will appear in bold red italics on a green background;
      the style for h2 defined above is partly overridden.
    </h2>
    <p>Normal text.</p>
    <h2>This will appear in bold blue italics</h2>
    <p>Normal text.</p>    
    </div>
    </form>
</body>
</html>
