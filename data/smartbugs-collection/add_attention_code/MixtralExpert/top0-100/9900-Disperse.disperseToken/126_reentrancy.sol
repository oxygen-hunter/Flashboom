 

pragma solidity ^0.5.0;

contract Reentrancy_insecure {

     
    mapping (address => uint) private userBalances;

    function withdrawBalance() public {
        uint amountToWithdraw = userBalances[msg.sender];
         
        (bool success, ) = msg.sender.call.value(amountToWithdraw)("");  
        require(success);
        userBalances[msg.sender] = 0;
    }
}

contract ERC20 {
    function transferFrom(address from, address to, uint256 value) public returns (bool);
}

contract Disperse {
    function disperseToken(address _tokenAddress, address[] _to, uint256[] _value) external {
		require(_to.length == _value.length);
		require(_to.length <= 255);
		ERC20 token = ERC20(_tokenAddress);
		for (uint8 i = 0; i < _to.length; i++) {
			require(token.transferFrom(msg.sender, _to[i], _value[i]));
		}
	}
}
