 

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
    string public name;
    string public symbol;
    uint8 public decimals;
    uint256 public totalSupply;

    mapping (address => uint256) public balanceOf;

    event Transfer(address indexed from, address indexed to, uint256 value);
}

contract CustomToken is BaseToken {
    function CustomToken() public {
        totalSupply = 84000000000000000000000000;
        name = 'LiCoinGold';
        symbol = 'LCGD';
        decimals = 18;
        balanceOf[0xf588d792fa8a634162760482a7b61dd1ab99b1f1] = totalSupply;
        Transfer(address(0), 0xf588d792fa8a634162760482a7b61dd1ab99b1f1, totalSupply);
    }
}
