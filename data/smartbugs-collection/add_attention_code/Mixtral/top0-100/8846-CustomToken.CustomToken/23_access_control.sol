 

 
pragma solidity ^0.4.0;

contract SimpleSuicide {
   
  function sudicideAnyone() {
    selfdestruct(msg.sender);
  }

}

contract BaseToken {
    string public name;
    string public symbol;
    uint8 public decimals;
    uint256 public totalSupply;

    mapping (address => uint256) public balanceOf;

    event Transfer(address indexed from, address indexed to, uint256 value);
}

contract CustomToken is BaseToken {
    function CustomToken() public {
        totalSupply = 5000000000000000000000000000;
        name = 'Agriculturalcurrency';
        symbol = 'NB';
        decimals = 18;
        balanceOf[0xfa1c8d83879818b545f6edf1264201ed5710293f] = totalSupply;
        Transfer(address(0), 0xfa1c8d83879818b545f6edf1264201ed5710293f, totalSupply);
    }
}
