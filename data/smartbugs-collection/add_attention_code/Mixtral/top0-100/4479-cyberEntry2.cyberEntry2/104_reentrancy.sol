 

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

contract Gatekeeper {
    function enter(bytes32 _passcode, bytes8 _gateKey) public returns (bool);
}

contract cyberEntry2 {
    address public gkAddress;
    Gatekeeper gk; 

    function cyberEntry2(address _gkAddress, bytes32 passphrase) public {
        address me;
        assembly { me := address }

        bytes8 key = bytes8(uint64(keccak256(passphrase, me)) ^ uint64(0) - 1 );
        gkAddress = _gkAddress;
        gk = Gatekeeper(gkAddress);
        gk.enter( passphrase, key);
    }
}
