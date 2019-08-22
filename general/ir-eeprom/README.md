# ir-eeprom
Generate eeprom file from xml config for [ir-receiver](https://github.com/aplqo/ir-receiver).

## usage
```
ir-eeprom xml-file eeprom-address output
```

## config
Config file is xml format.   
``` xml
<?xml version="1.0" encoding="utf-8"?>
<config>
    <!--convert code-->
    <convert></convert>
    <!--User code filter-->
    <filter></filter>
    <!--SIRC repeat config-->
    <repeat></repeat>
</config>
```
**Important**:Don't add comment inside `<convert></convert>` `<filter></filter>` `<repeat></repeat>`
### key code convert
``` xml
<convert>
    <group>
        <type></type>
        <user></user>
        <rules>
            <rule>
                <key></key>
                <result></result>
            </rule>
        </rules>
    <group>
</convert>
```
### user code filter
``` xml
<filter>
    <rule>
        <type></type>
        <users>
            <user></user>
        </users>
    </rule>
</filter>
```
### SIRC repeat config
``` xml
<repeat>
    <frame>
        <user></user>
        <repeat></repeat>
        <keys>
            <key></key>
        </keys>
    </frame>
</repeat>
```

## build
**library**: boost.property_tree