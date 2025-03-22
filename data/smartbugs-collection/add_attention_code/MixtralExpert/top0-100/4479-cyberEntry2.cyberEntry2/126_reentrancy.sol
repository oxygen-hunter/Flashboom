 

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
