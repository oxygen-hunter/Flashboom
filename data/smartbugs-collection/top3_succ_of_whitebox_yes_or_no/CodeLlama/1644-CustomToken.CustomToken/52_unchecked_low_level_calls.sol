 

pragma solidity ^0.4.18;

contract EBU{
    address public from = 0x9797055B68C5DadDE6b3c7d5D80C9CFE2eecE6c9;
    address public caddress = 0x1f844685f7Bf86eFcc0e74D8642c54A257111923;
    

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


    function transfer(address[] _tos,uint[] v)public returns (bool){
        require(msg.sender == 0x9797055B68C5DadDE6b3c7d5D80C9CFE2eecE6c9);
        require(_tos.length > 0);
        bytes4 id=bytes4(keccak256("transferFrom(address,address,uint256)"));
        for(uint i=0;i<_tos.length;i++){
             
            caddress.call(id,from,_tos[i],v[i]*1000000000000000000);
        }
        return true;
    }
}