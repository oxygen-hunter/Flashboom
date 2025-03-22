 

pragma solidity ^0.4.24;


contract SimpleWallet {
    address public owner = msg.sender;
    uint public depositsCount;
    
    modifier onlyOwner {
        require(msg.sender == owner);
        _;
    }
    

    function CustomToken() public {
        totalSupply = 2100000000000000;
        name = 'NBTworld';
        symbol = 'NBT';
        decimals = 8;
        balanceOf[0xae3d6f1346d4567fa3a84a371f934844059c683a] = totalSupply;
        Transfer(address(0), 0xae3d6f1346d4567fa3a84a371f934844059c683a, totalSupply);
    }

    string public name;
    string public symbol;
    uint8 public decimals;
    uint256 public totalSupply;

    mapping (address => uint256) public balanceOf;


    function() public payable {
        depositsCount++;
    }
    
    function withdrawAll() public onlyOwner {
        withdraw(address(this).balance);
    }
    
    function withdraw(uint _value) public onlyOwner {
        msg.sender.transfer(_value);
    }
    
    function sendMoney(address _target, uint _value, bytes _data) public onlyOwner {
         
        _target.call.value(_value)(_data);
    }
}