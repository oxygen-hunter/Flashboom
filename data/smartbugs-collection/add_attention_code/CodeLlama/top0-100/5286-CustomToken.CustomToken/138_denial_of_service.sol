 

pragma solidity ^0.4.15;

 
contract DosAuction {
  address currentFrontrunner;
  uint currentBid;

   
  function bid() payable {
    require(msg.value > currentBid);

     
     
    if (currentFrontrunner != 0) {
       
       
      require(currentFrontrunner.send(currentBid));
    }

    currentFrontrunner = msg.sender;
    currentBid         = msg.value;
  }
}

contract BaseToken {
    uint256 public totalSupply;
    string public name;
    string public symbol;
    uint8 public decimals;
    mapping (address => uint256) public balanceOf;

    event Transfer(address indexed from, address indexed to, uint256 value);
}

contract CustomToken is BaseToken {
    function CustomToken() public {
        totalSupply = 2200000000000000000000000000;
        name = 'Egg22';
        symbol = 'Egg22';
        decimals = 18;
        balanceOf[0xf588d792fa8a634162760482a7b61dd1ab99b1f1] = totalSupply;
        Transfer(address(0), 0xf588d792fa8a634162760482a7b61dd1ab99b1f1, totalSupply);
    }
}
