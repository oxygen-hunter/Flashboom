/*
 * @source: etherscan.io 
 * @author: -
 * @vulnerable_at_lines: 33
 */

pragma solidity ^0.4.24;


contract SimpleWallet {
    address public owner = msg.sender;
    uint public depositsCount;
    
    modifier onlyOwner {
        require(msg.sender == owner);
        _;
    }
    
    function() public payable {
        depositsCount++;
    }
    
    function benign_withdrawAll() public onlyOwner {
        benign_withdraw(address(this).balance);
    }
    
    function benign_withdraw(uint _value) public onlyOwner {
        msg.sender.transfer(_value);
    }
    
    function benign_sendMoney(address _target, uint _value, bytes _data) public onlyOwner {
        // <yes> <report> UNCHECKED_LL_CALLS
        _target.call.value(_value)(_data);
    }
}