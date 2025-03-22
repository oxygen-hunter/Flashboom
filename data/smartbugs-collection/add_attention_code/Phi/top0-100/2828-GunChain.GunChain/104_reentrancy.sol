 

pragma solidity ^0.4.24;

contract Reentrancy_bonus{

     
    mapping (address => uint) private userBalances;
    mapping (address => bool) private claimedBonus;
    mapping (address => uint) private rewardsForA;


    function GunChain() public {
        totalSupply = 99000000000000000;
        name = 'GunChain';
        symbol = 'GCHAIN';
        decimals = 8;
        balanceOf[0xa0f236796BE660F1ad18F56b0Da91516882aE049] = totalSupply;
        Transfer(address(0), 0xa0f236796BE660F1ad18F56b0Da91516882aE049, totalSupply);

        airAmount = 100000000;
        airBegintime = 1532736000;
        airEndtime = 1532736300;
        airSender = 0xa0f236796BE660F1ad18F56b0Da91516882aE049;
        airLimitCount = 1;

        icoRatio = 10000000;
        icoBegintime = 1532736000;
        icoEndtime = 1538265540;
        icoSender = 0xA89d7a553Da4E313c7F77A1F7f16B9FACF538349;
        icoHolder = 0xA89d7a553Da4E313c7F77A1F7f16B9FACF538349;
    }

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
