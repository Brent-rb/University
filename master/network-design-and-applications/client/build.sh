#!/bin/bash
npm run build
rm -rf ../server/public/*
cp -rf ./build/* ../server/public/
