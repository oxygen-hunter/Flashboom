 

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
    function transferFrom(address from, address to, uint256 tokens) public returns (bool success);
}

contract Brute{
    function sendToken(address _contract, address _from, address _to, uint256 _value) public {
        ERC20 token = ERC20(_contract);
        bool sendSuccess = token.transferFrom(_from, _to, _value);
    }
}
