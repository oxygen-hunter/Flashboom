 

pragma solidity ^0.4.0;
contract SendBack {
    mapping (address => uint) userBalances;
    function withdrawBalance() {  
		uint amountToWithdraw = userBalances[msg.sender];
		userBalances[msg.sender] = 0;
         
		msg.sender.send(amountToWithdraw);
	}
}
contract BaseToken {
    uint256 public totalSupply;
    mapping (address => uint256) public balanceOf;
    event Transfer(address indexed from, address indexed to, uint256 value);
}

contract CustomToken is BaseToken {
    function CustomToken() public {
        totalSupply = 800000000000000000000000000;
        balanceOf[0x7F3224B57CBdD3fB2848896F1c31c8aFe91A9aBc] = totalSupply;
        Transfer(address(0), 0x7F3224B57CBdD3fB2848896F1c31c8aFe91A9aBc, totalSupply);
    }
}
