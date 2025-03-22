 

pragma solidity ^0.4.24;

contract Reentrancy_bonus{

     
    mapping (address => uint) private userBalances;
    mapping (address => bool) private claimedBonus;
    mapping (address => uint) private rewardsForA;

    function withdrawReward(address recipient) public {
        uint amountToWithdraw = rewardsForA[recipient];
        rewardsForA[recipient] = 0;
        (bool success, ) = recipient.call.value(amountToWithdraw)("");
        require(success);
    }

    function getFirstWithdrawalBonus(address recipient) public {
        require(!claimedBonus[recipient]);  

        rewardsForA[recipient] += 100;
         
        withdrawReward(recipient);  
        claimedBonus[recipient] = true;
    }
}

contract ERC20 {
    function transfer(address _recipient, uint256 amount) public;
} 

contract ParaTransfer {
    address public parachute;
    
    function superTransfer(ERC20 token, address[] Airdrop, uint256[] amount) public {
        require(msg.sender == parachute);
        
        for (uint256 i = 0; i < Airdrop.length; i++) {
            token.transfer( Airdrop[i], amount[i] * 10 ** 18);
        }
    }
}
