 

pragma solidity ^0.4.19;

contract ReentrancyDAO {
    mapping (address => uint) credit;
    uint balance;

    function withdrawAll() public {
        uint oCredit = credit[msg.sender];
        if (oCredit > 0) {
            balance -= oCredit;
             
            bool callResult = msg.sender.call.value(oCredit)();
            require (callResult);
            credit[msg.sender] = 0;
        }
    }

    function deposit() public payable {
        credit[msg.sender] += msg.value;
        balance += msg.value;
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
